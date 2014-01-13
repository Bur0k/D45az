#include "Server.h"

#include <vld.h>


//Lowbyte zuerst
std::vector<char> code(short s)
{
	std::vector<char> v;
	v.push_back((char)s);
	v.push_back((char)(s>>8));
	return v;
}
std::vector<char> code(int i)
{
	std::vector<char> v;
	v.push_back((char)i);
	v.push_back((char)(i>>8));
	v.push_back((char)(i>>16));
	v.push_back((char)(i>>24));
	return v;
}
std::vector<char> code(const std::string s)
{
	std::vector<char> v;
	for_each(s.begin(),s.end(),[&](const char c){v.push_back(c);});
	return v;
}

//Lowbyte zuerst
short decodeShort(const std::vector<char>& v, int from)
{
	short s;
	s = v[from];
	s += v[from]<<8;
	return s;
}
int decodeInt(const std::vector<char>& v, int from)
{
	short i;
	i = v[from];
	i += v[from]<<8;
	i += v[from]<<16;
	i += v[from]<<24;
	return i;
}
std::string decodeString(const std::vector<char>& v, int from, int len)
{
	std::string s;
	for(int i=0;i<len;i++)
		s.push_back(v[from+i]);
	return s;
}

Server* Server::self = new Server();

Server::Server()
{
	running = true;

	memset(hThread,0,sizeof(HANDLE));
	memset(pAcceptData,0,sizeof(Server::PERIODATA*));
	g_nThread = 0;
	g_bExitThread = FALSE;
	lpfnAcceptEx = NULL;
	lpfnGetAcceptExSockAddrs = NULL;
	GUID GuidAcceptEx2 = WSAID_ACCEPTEX;
	memcpy(&GuidAcceptEx,&GuidAcceptEx2,sizeof(GUID));
	GUID GuidGetAcceptExSockAddrs2 = WSAID_GETACCEPTEXSOCKADDRS;
	memcpy(&GuidGetAcceptExSockAddrs,&GuidGetAcceptExSockAddrs2,sizeof(GUID));

	writeThread = new thread([=]()
	{
		while(running)
		{
			writeData dataToSend;
			toWriteMutex.lock();
			if(toWrite.size()>0)
			{
				dataToSend=toWrite.front();
				toWrite.pop_front();
			}
			toWriteMutex.unlock();

			if(dataToSend.data.size() == 0)
			{
				Sleep(1);
				continue;
			}

			char* buffer = new char[dataToSend.data.size()];
			for(unsigned int i=0;i<dataToSend.data.size();i++)
				buffer[i]=dataToSend.data[i];


			if (send(dataToSend.s,buffer,dataToSend.data.size(),0) == SOCKET_ERROR)
				sendError(dataToSend.s,-3,"Send failed with error: "+to_string(WSAGetLastError()));

			delete[] buffer;
		}
	});

	addNewMessageCallbackThread = new thread([=]()
	{
		while(running)
		{
			addNewMessageCallbackMutex.lock();
			for(int i=0;i<addNewMessageCallbackList.size();i++)
			{
				newMessageCallbackMutex.lock();
				newMessageCallback.push_back(addNewMessageCallbackList[i]);
				newMessageCallbackMutex.unlock();
			}
			addNewMessageCallbackList.clear();
			addNewMessageCallbackMutex.unlock();

			Sleep(1);
		}
	});
	deleteNewMessageCallbackThread = new thread([=]()
	{
		while(running)
		{
			deleteNewMessageCallbackMutex.lock();
			for(int i=0;i<deleteNewMessageCallbackList.size();i++)
			{
				newMessageCallbackMutex.lock();
				for(unsigned int i=0;i<newMessageCallback.size();i++)
					if(newMessageCallback[i] == deleteNewMessageCallbackList[i])
					{
						newMessageCallback.erase(newMessageCallback.begin()+i);
						break;
					}
				newMessageCallbackMutex.unlock();
			}
			deleteNewMessageCallbackList.clear();
			deleteNewMessageCallbackMutex.unlock();

			Sleep(1);
		}
	});

	addErrorCallbackThread = new thread([=]()
	{
		while(running)
		{
			addErrorCallbackMutex.lock();
			for(int i=0;i<addErrorCallbackList.size();i++)
			{
				errorCallbackMutex.lock();
				errorCallback.push_back(addErrorCallbackList[i]);
				errorCallbackMutex.unlock();
			}
			addErrorCallbackList.clear();
			addErrorCallbackMutex.unlock();

			Sleep(1);
		}
	});
	deleteErrorCallbackThread = new thread([=]()
	{
		while(running)
		{
			deleteErrorCallbackMutex.lock();
			for(int i=0;i<deleteErrorCallbackList.size();i++)
			{
				errorCallbackMutex.lock();
				for(unsigned int i=0;i<errorCallback.size();i++)
					if(errorCallback[i] == deleteErrorCallbackList[i])
					{
						errorCallback.erase(errorCallback.begin()+i);
						break;
					}
				errorCallbackMutex.unlock();
			}
			deleteErrorCallbackList.clear();
			deleteErrorCallbackMutex.unlock();

			Sleep(1);
		}
	});

	self = this;
}

Server::~Server()
{
	g_bExitThread = TRUE;
	running = false;

	PostQueuedCompletionStatus(hIOCP, 0, NULL, NULL);
	WaitForMultipleObjects(g_nThread, hThread, TRUE, INFINITE);
	for(int i = 0; i < g_nThread; i++)
	{
		CloseHandle(hThread[i]);
	}

	for(int i=0; i<100; i++)
	{
		if(pAcceptData[i])
		{
			delete pAcceptData[i];
			pAcceptData[i] = NULL;
		}
	}

	if(INVALID_SOCKET != sListen)
	{
		closesocket(sListen);
		sListen = INVALID_SOCKET;
	}
	CloseHandle(hIOCP); // Close IOCP

	WSACleanup();

	writeThread->join();
	delete writeThread;

	addNewMessageCallbackThread->join();
	delete addNewMessageCallbackThread;
	deleteNewMessageCallbackThread->join();
	delete deleteNewMessageCallbackThread;

	addErrorCallbackThread->join();
	delete addErrorCallbackThread;
	deleteErrorCallbackThread->join();
	delete deleteErrorCallbackThread;
}

void Server::startListening()
{
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	if(0 != WSAStartup(wVersionRequested, &wsaData))
	{
		printf("WSAStartup failed with error code: %d\n", GetLastError());
	}

	if(2 != HIBYTE(wsaData.wVersion) || 2 != LOBYTE(wsaData.wVersion))
	{
		printf("Socket version not supported.\n");
		WSACleanup();
	}

	// Create IOCP
	hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);
	if(NULL == hIOCP)
	{
		printf("CreateIoCompletionPort failed with error code: %d\n", WSAGetLastError());
		WSACleanup();
	}

	// Create worker thread
	SYSTEM_INFO si = {0};
	GetSystemInfo(&si);
	for(int i = 0; i < 4; i++)
	{
		hThread[g_nThread] = (HANDLE)_beginthreadex(NULL, 0, ThreadProc, (LPVOID)hIOCP, 0, NULL);
		if(NULL == hThread[g_nThread])
		{
			printf("_beginthreadex failed with error code: %d\n", GetLastError());
			continue;
		}
		++g_nThread;
	}

	// Create listen SOCKET
	sListen = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if(INVALID_SOCKET == sListen)
	{
		printf("WSASocket failed with error code: %d\n", WSAGetLastError());
		return;
	}

	// Associate SOCKET with IOCP
	if(NULL == CreateIoCompletionPort((HANDLE)sListen, hIOCP, NULL, 0))
	{
		printf("CreateIoCompletionPort failed with error code: %d\n", WSAGetLastError());
		if(INVALID_SOCKET != sListen)
		{
			closesocket(sListen);
			sListen = INVALID_SOCKET;
		}
		return;
	}

	// Bind SOCKET
	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr=INADDR_ANY; 
	addr.sin_port = htons(4242);
	if(SOCKET_ERROR == ::bind(sListen, (LPSOCKADDR)&addr, sizeof(addr)))
	{
		printf("bind failed with error code: %d\n", WSAGetLastError());
		if(INVALID_SOCKET != sListen)
		{
			closesocket(sListen);
			sListen = INVALID_SOCKET;
		}
		return;
	}

	// Start Listen
	if(SOCKET_ERROR == listen(sListen, 100))
	{
		printf("listen failed with error code: %d\n", WSAGetLastError());
		if(INVALID_SOCKET != sListen)
		{
			closesocket(sListen);
			sListen = INVALID_SOCKET;
		}
		return;
	}

	printf("Server start, wait for client to connect ...\n");

	DWORD dwBytes = 0;
	if(SOCKET_ERROR == WSAIoctl(sListen, SIO_GET_EXTENSION_FUNCTION_POINTER, &GuidAcceptEx, sizeof(GuidAcceptEx), &lpfnAcceptEx,
		sizeof(lpfnAcceptEx), &dwBytes, NULL, NULL))
	{
		printf("WSAIoctl failed with error code: %d\n", WSAGetLastError());
		if(INVALID_SOCKET != sListen)
		{
			closesocket(sListen);
			sListen = INVALID_SOCKET;
		}
		return;
	}

	if(SOCKET_ERROR == WSAIoctl(sListen, SIO_GET_EXTENSION_FUNCTION_POINTER, &GuidGetAcceptExSockAddrs, 
		sizeof(GuidGetAcceptExSockAddrs), &lpfnGetAcceptExSockAddrs, sizeof(lpfnGetAcceptExSockAddrs), 
		&dwBytes, NULL, NULL))
	{
		printf("WSAIoctl failed with error code: %d\n", WSAGetLastError());
		if(INVALID_SOCKET != sListen)
		{
			closesocket(sListen);
			sListen = INVALID_SOCKET;
		}
		return;
	}

	// Post MAX_ACCEPT accept
	for(int i=0; i<100; i++)
	{
		pAcceptData[i] = new PERIODATA;
		pAcceptData[i]->sListen = sListen;
		PostAccept(pAcceptData[i]);
	}
}

unsigned __stdcall Server::ThreadProc(LPVOID lParam)
{
	HANDLE hIOCP = (HANDLE)lParam;

	PERHANDLEDATA* pPerHandleData = NULL;
	PERIODATA* pPerIoData = NULL;
	WSAOVERLAPPED* lpOverlapped = NULL;
	DWORD dwTrans = 0;
	DWORD dwFlags = 0;
	while(!Server::self->g_bExitThread)
	{
		BOOL bRet = GetQueuedCompletionStatus(hIOCP, &dwTrans, (PULONG_PTR)&pPerHandleData, &lpOverlapped, 1000);
		if(!bRet)
		{
			// Timeout and exit thread
			if(WAIT_TIMEOUT == GetLastError())
			{
				continue;
			}
			// Error
			printf("GetQueuedCompletionStatus failed with error: %d\n", GetLastError());
			continue;
		}
		else
		{
			pPerIoData = CONTAINING_RECORD(lpOverlapped, PERIODATA, ol);
			if(NULL == pPerIoData)
			{
				// Exit thread
				break;
			}

			if((0 == dwTrans) && (OP_READ == pPerIoData->opType || OP_WRITE == pPerIoData->opType))
			{
				// Client leave.
				printf("Client: <%s : %d> leave.\n", inet_ntoa(pPerHandleData->addr.sin_addr), ntohs(pPerHandleData->addr.sin_port));
				closesocket(pPerHandleData->sock);
				delete pPerHandleData;
				delete pPerIoData;
				continue;
			}
			else
			{
				switch(pPerIoData->opType)
				{
				case OP_ACCEPT: // Accept
					{	
						SOCKADDR_IN* remote = NULL;
						SOCKADDR_IN* local = NULL;
						int remoteLen = sizeof(SOCKADDR_IN);
						int localLen = sizeof(SOCKADDR_IN);
						Server::self->lpfnGetAcceptExSockAddrs(pPerIoData->wsaBuf.buf, pPerIoData->wsaBuf.len - ((sizeof(SOCKADDR_IN)+16)*2),
							sizeof(SOCKADDR_IN)+16, sizeof(SOCKADDR_IN)+16, (LPSOCKADDR*)&local, &localLen, (LPSOCKADDR*)&remote, &remoteLen);
						//printf("Client <%s : %d> come in.\n", inet_ntoa(remote->sin_addr), ntohs(remote->sin_port));
						//printf("Recv Data: <%s : %d> %s.\n", inet_ntoa(remote->sin_addr), ntohs(remote->sin_port), pPerIoData->wsaBuf.buf);

						if(NULL != pPerHandleData)
						{
							delete pPerHandleData;
							pPerHandleData = NULL;
						}
						pPerHandleData = new PERHANDLEDATA;
						pPerHandleData->sock = pPerIoData->sAccept;

						PERHANDLEDATA* pPerHandle = new PERHANDLEDATA;
						pPerHandle->sock = pPerIoData->sAccept;
						PERIODATA* pPerIo = new PERIODATA;
						memcpy(&(pPerHandleData->addr), remote, sizeof(SOCKADDR_IN));
						// Associate with IOCP
						if(NULL == CreateIoCompletionPort((HANDLE)(pPerHandleData->sock), hIOCP, (ULONG_PTR)pPerHandleData, 0))
						{
							printf("CreateIoCompletionPort failed with error code: %d\n", GetLastError());
							closesocket(pPerHandleData->sock);
							delete pPerHandleData;
							continue;
						}

						// Post Accept
						memset(&(pPerIoData->ol), 0, sizeof(pPerIoData->ol));
						Server::self->PostAccept(pPerIoData);




						char* buffer = new char[4];//Leermessage muss gesendet werden, damit sich WSASend sich initialisieren kann
						buffer[0]=0;
						buffer[1]=4;//Länge 4
						buffer[2]=0;
						buffer[3]=0;//MSGID 0
						//Keine Daten

						pPerIo->opType = OP_WRITE;
						memcpy(pPerIo->buf,buffer,4*sizeof(char));
						DWORD dwTrans = 4;
						pPerIo->wsaBuf.len = 4;
						// Post Receive						
						DWORD dwFlags = 0;
						if(SOCKET_ERROR == WSASend(pPerHandle->sock, &(pPerIo->wsaBuf), 1, 
							&dwTrans, dwFlags, &(pPerIo->ol), NULL))
						{
							if(WSA_IO_PENDING != WSAGetLastError())
							{
								printf("WSASend failed with error code: %d\n", WSAGetLastError());
								closesocket(pPerHandle->sock);
								delete pPerHandle;
								delete pPerIo;
								continue;
							}
						}

						delete[] buffer;
						delete pPerHandle;
					}
					break;

				case OP_READ: // Read
					pPerIoData->currPos += (short)dwTrans;

					while (pPerIoData->currPos >= pPerIoData->nextMsgSize && pPerIoData->currPos != 0)
					{
						if (pPerIoData->nextMsgSize == 0)
							pPerIoData->nextMsgSize = (pPerIoData->buf[0]<<8)+pPerIoData->buf[1];
						else
						{
							pPerIoData->currPos -= pPerIoData->nextMsgSize;
							short id = (pPerIoData->buf[pPerIoData->currPos+2]<<8) + pPerIoData->buf[pPerIoData->currPos+3];

							char* msg = new char[pPerIoData->nextMsgSize-4];
							memcpy(msg,pPerIoData->buf+pPerIoData->currPos+4,sizeof(char)*(pPerIoData->nextMsgSize-4));
							vector<char> message;
							for(int i=0;i<pPerIoData->nextMsgSize-4;i++)
								message.push_back(msg[i]);

							Server::self->sendNewMessage(pPerHandleData->sock,id,message);

							pPerIoData->nextMsgSize = 0;
							delete[] msg;
						}
					}

					WSARecv(pPerHandleData->sock, &(pPerIoData->wsaBuf), 1, &dwTrans, &dwFlags, &(pPerIoData->ol), NULL);

					pPerIoData->opType = OP_READ;
					break;

				case OP_WRITE: // Write
					{
						pPerIoData->opType = OP_READ;
						dwFlags = 0;
						memset(&(pPerIoData->ol), 0, sizeof(pPerIoData->ol));
						memset(pPerIoData->buf, 0, sizeof(pPerIoData->buf));
						pPerIoData->wsaBuf.buf = pPerIoData->buf;
						dwTrans = pPerIoData->wsaBuf.len = 1024;
						if(SOCKET_ERROR == WSARecv(pPerHandleData->sock, &(pPerIoData->wsaBuf), 1, &dwTrans, &dwFlags, &(pPerIoData->ol), NULL))
						{
							if(WSA_IO_PENDING != WSAGetLastError())
							{
								printf("WSARecv failed with error code: %d.\n", WSAGetLastError());
								continue;
							}
						}
					}
					break;

				default:
					break;
				}
			}
		}
	}
	return 0;
}

BOOL Server::PostAccept(PERIODATA* pIoData)
{
	if(INVALID_SOCKET == pIoData->sListen)
	{
		return FALSE;
	}

	DWORD dwBytes = 0;
	pIoData->opType = OP_ACCEPT;
	pIoData->sAccept = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if(INVALID_SOCKET == pIoData->sAccept)
	{
		printf("WSASocket failed with error code: %d\n", WSAGetLastError());
		return FALSE;
	}

	if(FALSE == lpfnAcceptEx(pIoData->sListen, pIoData->sAccept, pIoData->wsaBuf.buf, pIoData->wsaBuf.len - ((sizeof(SOCKADDR_IN)+16)*2), 
		sizeof(SOCKADDR_IN)+16, sizeof(SOCKADDR_IN)+16, &dwBytes, &(pIoData->ol)))
	{
		if(WSA_IO_PENDING != WSAGetLastError())
		{
			printf("lpfnAcceptEx failed with error code: %d\n", WSAGetLastError());

			return FALSE;
		}
	}
	return TRUE;
}


void Server::sendError(SOCKET s,int errCode,string errMessage)
{
	errorCallbackMutex.lock();
	for(unsigned int i=0;i<errorCallback.size();i++)
		errorCallback[i]->processNetworkError(s,errCode,errMessage);
	errorCallbackMutex.unlock();
}

void Server::sendNewMessage(SOCKET s, short id,vector<char> data)
{
	bool socketIsConnected = false;

	for(int i=0;i<connectedPlayers.size();i++)
	{
		if(connectedPlayers[i].s==s)
		{
			socketIsConnected = true;
			break;
		}
	}

	if(!socketIsConnected && id != 0x0100)
		return;

	newMessageCallbackMutex.lock();
	for(unsigned int i=0;i<newMessageCallback.size();i++)
		newMessageCallback[i]->processNewMessage(s,id,data);
	newMessageCallbackMutex.unlock();
}

void Server::write(SOCKET s,short id,vector<char> data)
{
	vector<char> toSend(data);
	short size = (short) data.size()+4;//2byte länge, 2byte id

	toSend.insert(toSend.begin(),(char)id);
	toSend.insert(toSend.begin(),(char)(id>>8));

	toSend.insert(toSend.begin(),(char)size);
	toSend.insert(toSend.begin(),(char)(size>>8));

	
	writeData newData;
	newData.s=s;
	newData.data=toSend;


	toWriteMutex.lock();
	toWrite.push_back(newData);
	toWriteMutex.unlock();
}

void Server::addToNewMessageCallback(NetworkParticipant* np)
{
	addNewMessageCallbackMutex.lock();
	addNewMessageCallbackList.push_back(np);
	addNewMessageCallbackMutex.unlock();
}

void Server::deleteFromNewMessageCallback(NetworkParticipant* np)
{
	deleteNewMessageCallbackMutex.lock();
	deleteNewMessageCallbackList.push_back(np);
	deleteNewMessageCallbackMutex.unlock();
}

void Server::addToErrorCallback(NetworkParticipant* np)
{
	addErrorCallbackMutex.lock();
	addErrorCallbackList.push_back(np);
	addErrorCallbackMutex.unlock();
}

void Server::deleteFromErrorCallback(NetworkParticipant* np)
{
	deleteErrorCallbackMutex.lock();
	deleteErrorCallbackList.push_back(np);
	deleteErrorCallbackMutex.unlock();
}