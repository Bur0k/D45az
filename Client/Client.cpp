#include "Client.h"

#include <vld.h>

//Lowbyte zuerst
std::vector<char> code(short s)
{
	std::vector<char> v;
	v.push_back(s);
	v.push_back(s>>8);
	return v;
}
std::vector<char> code(int i)
{
	std::vector<char> v;
	v.push_back(i);
	v.push_back(i>>8);
	v.push_back(i>>16);
	v.push_back(i>>24);
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


Client* Client::self = new Client();

Client::Client()
{
	running=true;
	readThread = NULL;

}

Client::~Client()
{
	running = false;

	if(readThread!=NULL)
	{
		readThread->join();
		delete readThread;
	}

	closesocket(s);

	

	addNewMessageCallbackThread->join();
	delete addNewMessageCallbackThread;
	deleteNewMessageCallbackThread->join();
	delete deleteNewMessageCallbackThread;

	addErrorCallbackThread->join();
	delete addErrorCallbackThread;
	deleteErrorCallbackThread->join();
	delete deleteErrorCallbackThread;
}

void Client::connectToServer(string ip, int port)
{
	WSADATA wsa;

	if(WSAStartup(MAKEWORD(2,0),&wsa))
	{
		sendError(-4,"WSAStartup failed: "+to_string(WSAGetLastError()));
		return ;
	}


	s=socket(AF_INET,SOCK_STREAM,0);

	if(s==INVALID_SOCKET)
	{
		sendError(-1,"Socket could not be created: "+to_string(WSAGetLastError()));
		return ;
	}

	sockaddr_in si;
	hostent *hostess_twinkies = gethostbyname(ip.c_str());

	si.sin_family = AF_INET;
	si.sin_port = htons(port);
	si.sin_addr = *((in_addr*) hostess_twinkies->h_addr);
	memset(&(si.sin_zero), 0, 8);
	if (connect(s, (sockaddr*) &si, sizeof(struct sockaddr)) == -1)
	{
		sendError(-2,"Socket could not connect: "+to_string(WSAGetLastError()));
		return ;
	}

	u_long nonBlockMode = 1;
	if (ioctlsocket(s, FIONBIO, &nonBlockMode) != NO_ERROR)
	{
		sendError(-5,"Could not set Non-Blocking mode: "+to_string(WSAGetLastError()));
		return ;
	}


	
	writeThread = new thread([=]()
	{
		while(running)
		{
			vector<char> dataToSend;
			toWriteMutex.lock();
			if(toWrite.size()>0)
			{
				dataToSend=toWrite.front();
				toWrite.pop_front();
			}
			toWriteMutex.unlock();

			if(dataToSend.size() == 0)
				continue;

			char* buffer = new char[dataToSend.size()];
			for(unsigned int i=0;i<dataToSend.size();i++)
				buffer[i]=dataToSend[i];


			if (send(s,buffer,dataToSend.size(),0) == SOCKET_ERROR)
				sendError(-3,"Send failed with error: "+to_string(WSAGetLastError()));

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
}


void Client::sendError(int errCode,string errMessage)
{
	errorCallbackMutex.lock();
	for(unsigned int i=0;i<errorCallback.size();i++)
		errorCallback[i]->processNetworkError(errCode,errMessage);
	errorCallbackMutex.unlock();
}

void Client::sendNewMessage(short id,vector<char> data)
{
	newMessageCallbackMutex.lock();
	for(unsigned int i=0;i<newMessageCallback.size();i++)
		newMessageCallback[i]->processNewMessage(id,data);
	newMessageCallbackMutex.unlock();
}

void Client::write(short id, vector<char>data)
{
	vector<char> toSend(data);
	short size = (short) data.size()+4;//2byte länge, 2byte id

	toSend.insert(toSend.begin(),(char)id);
	toSend.insert(toSend.begin(),(char)(id>>8));

	toSend.insert(toSend.begin(),(char)size);
	toSend.insert(toSend.begin(),(char)(size>>8));


	toWriteMutex.lock();
	toWrite.push_back(toSend);
	toWriteMutex.unlock();
}

void Client::beginRead()
{
	if(readThread)
		return;
	readThread = new thread([=]()
	{
		while(running)
		{
			static char buffer[1024];
			static short currPos = 0;
			static short nextMsgSize = 0;
			
			Sleep(1);

			int recievedBytes = recv(s,buffer+currPos,1024-currPos,0);
			if(recievedBytes == 0)
				;//Connection closed
			else if(recievedBytes <0)
			{
				if(WSAGetLastError() == 10035)//Would block
					continue;
				else//Anderer ECHTER Fehler
				{
					running = false;
					sendNewMessage(-1,vector<char>());
					break;
				}
			}
			
			currPos += recievedBytes;
			while (currPos >= nextMsgSize && currPos != 0)
			{
				if (nextMsgSize == 0)
					nextMsgSize = (buffer[0]<<8)+buffer[1];
				else
				{
					currPos -= nextMsgSize;
					short id = (buffer[currPos+2]<<8) + buffer[currPos+3];

					char* msg = new char[nextMsgSize-4];
					memcpy(msg,buffer+currPos+4,sizeof(char)*(nextMsgSize-4));
					vector<char> message;
					for(int i=0;i<nextMsgSize-4;i++)
						message.push_back(msg[i]);

					sendNewMessage(id,message);


					nextMsgSize = 0;
					delete[] msg;
				}
			}
		}
	});
}

void Client::addToNewMessageCallback(NetworkParticipant* np)
{
	addNewMessageCallbackMutex.lock();
	addNewMessageCallbackList.push_back(np);
	addNewMessageCallbackMutex.unlock();
}

void Client::deleteFromNewMessageCallback(NetworkParticipant* np)
{
	deleteNewMessageCallbackMutex.lock();
	deleteNewMessageCallbackList.push_back(np);
	deleteNewMessageCallbackMutex.unlock();
}

void Client::addToErrorCallback(NetworkParticipant* np)
{
	addErrorCallbackMutex.lock();
	addErrorCallbackList.push_back(np);
	addErrorCallbackMutex.unlock();
}

void Client::deleteFromErrorCallback(NetworkParticipant* np)
{
	deleteErrorCallbackMutex.lock();
	deleteErrorCallbackList.push_back(np);
	deleteErrorCallbackMutex.unlock();
}