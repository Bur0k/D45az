#include "Client.h"

#include <vld.h>

//Lowbyte zuerst
std::vector<char> code(short s)
{
	std::vector<char> v;
	v.push_back(static_cast<char>(s));
	v.push_back(static_cast<char>(s>>8));
	return v;
}
std::vector<char> code(int i)
{
	std::vector<char> v;
	v.push_back(static_cast<char>(i));
	v.push_back(static_cast<char>(i>>8));
	v.push_back(static_cast<char>(i>>16));
	v.push_back(static_cast<char>(i>>24));
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
	s += v[from+1]<<8;
	return s;
}
int decodeInt(const std::vector<char>& v, int from)
{
	short i;
	i = v[from];
	i += v[from+1]<<8;
	i += v[from+2]<<16;
	i += v[from+3]<<24;
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
		int bla=4;
		bla++;
	});
	cout<<writeThread->get_id()<<endl;

	addDeleteProcessNewMessageCallback = new thread([&]()
	{
		while(running)
		{
			//ADD 
			addNewMessageCallbackMutex.lock();
			std::vector<NetworkParticipant*> AVOIDING_DEADLOCK_KAK(addNewMessageCallbackList);
			addNewMessageCallbackList.clear();
			addNewMessageCallbackMutex.unlock();
			for(unsigned int i=0;i<AVOIDING_DEADLOCK_KAK.size();i++)
				newMessageCallback.push_back(AVOIDING_DEADLOCK_KAK[i]);
			//********* END ADD

			//PROCESS

			newMessageQueueMutex.lock();
			for(auto it : newMessageQueue)
			{
				NetworkParticipant** callback = new NetworkParticipant*[newMessageCallback.size()];
				int callbackSize = newMessageCallback.size();
				for(int i=0;i<newMessageCallback.size();i++)
					callback[i]=newMessageCallback[i];
				for(int i=0;i<callbackSize;i++)
				{
					if(callback[i]!=nullptr)
					{
						callback[i]->processNewMessage(it.id,it.data);

						//DELETE
						deleteNewMessageCallbackMutex.lock();
						AVOIDING_DEADLOCK_KAK = deleteNewMessageCallbackList;
						deleteNewMessageCallbackList.clear();
						deleteNewMessageCallbackMutex.unlock();
						for(unsigned int j=0;j<AVOIDING_DEADLOCK_KAK.size();j++)
						{
							for(unsigned int k=0;k<newMessageCallback.size();k++)
							{
								if(newMessageCallback[k] == AVOIDING_DEADLOCK_KAK[j])//Aus newMessageCallback LÖSChEN
								{
									for(int l=0;l<callbackSize;l++)//Callback eintrag auf nullptr setzen
									{
										if(newMessageCallback[k] == callback[l])
										{
											callback[l] = nullptr;
											break;
										}
									}//*****************************END CALLBACK EINTRAG
									newMessageCallback.erase(newMessageCallback.begin()+k);
									break;
								}//***************************************************END AUS newMessageCallback LÖSCHEN
							}
						}
						//**********END DELETE
					}
				}
				delete[] callback;
			}//**************** END PROCESS
			newMessageQueue.clear();
			newMessageQueueMutex.unlock();

			//DELETE
			deleteNewMessageCallbackMutex.lock();
			AVOIDING_DEADLOCK_KAK = deleteNewMessageCallbackList;
			deleteNewMessageCallbackList.clear();
			deleteNewMessageCallbackMutex.unlock();
			for(unsigned int i=0;i<AVOIDING_DEADLOCK_KAK.size();i++)
			{
				newMessageCallbackMutex.lock();
				for(unsigned int j=0;j<newMessageCallback.size();j++)
					if(newMessageCallback[j] == AVOIDING_DEADLOCK_KAK[i])
					{
						newMessageCallback.erase(newMessageCallback.begin()+j);
						break;
					}
				newMessageCallbackMutex.unlock();
			}
			//********** END DELETE
		}
	});

	addDeleteProcessErrorCallback = new thread([&]()
	{
		while(running)
		{
			//ADD 
			addErrorCallbackMutex.lock();
			std::vector<NetworkParticipant*> AVOIDING_DEADLOCK_KAK(addErrorCallbackList);
			addErrorCallbackList.clear();
			addErrorCallbackMutex.unlock();
			for(unsigned int i=0;i<AVOIDING_DEADLOCK_KAK.size();i++)
				errorCallback.push_back(AVOIDING_DEADLOCK_KAK[i]);
			//********* END ADD

			//PROCESS

			errorQueueMutex.lock();
			for(auto it : errorQueue)
			{
				NetworkParticipant** callback = new NetworkParticipant*[errorCallback.size()];
				int callbackSize = errorCallback.size();
				for(int i=0;i<errorCallback.size();i++)
					callback[i]=errorCallback[i];
				for(int i=0;i<callbackSize;i++)
				{
					if(callback[i]!=nullptr)
					{
						callback[i]->processNetworkError(it.errCode,it.errMessage);

						//DELETE
						deleteErrorCallbackMutex.lock();
						AVOIDING_DEADLOCK_KAK = deleteErrorCallbackList;
						deleteErrorCallbackList.clear();
						deleteErrorCallbackMutex.unlock();
						for(unsigned int j=0;j<AVOIDING_DEADLOCK_KAK.size();j++)
						{
							for(unsigned int k=0;k<errorCallback.size();k++)
							{
								if(errorCallback[k] == AVOIDING_DEADLOCK_KAK[j])//Aus errorCallback LÖSChEN
								{
									for(int l=0;l<callbackSize;l++)//Callback eintrag auf nullptr setzen
									{
										if(errorCallback[k] == callback[l])
										{
											callback[l] = nullptr;
											break;
										}
									}//*****************************END CALLBACK EINTRAG
									errorCallback.erase(errorCallback.begin()+k);
									break;
								}//***************************************************END AUS errorCallback LÖSCHEN
							}
						}
						//**********END DELETE
					}
				}
				delete[] callback;
			}//**************** END PROCESS
			errorQueue.clear();
			errorQueueMutex.unlock();

			//DELETE
			deleteErrorCallbackMutex.lock();
			AVOIDING_DEADLOCK_KAK = deleteErrorCallbackList;
			deleteErrorCallbackList.clear();
			deleteErrorCallbackMutex.unlock();
			for(unsigned int i=0;i<AVOIDING_DEADLOCK_KAK.size();i++)
			{
				errorCallbackMutex.lock();
				for(unsigned int j=0;j<errorCallback.size();j++)
					if(errorCallback[j] == AVOIDING_DEADLOCK_KAK[i])
					{
						errorCallback.erase(errorCallback.begin()+j);
						break;
					}
				errorCallbackMutex.unlock();
			}
			//********** END DELETE
		}
	});
}

Client::~Client()
{
	running = false;

	if(readThread!=NULL)
	{
		readThread->join();
		delete readThread;
	}
	if(writeThread!=NULL)
	{
		writeThread->join();
		delete writeThread;
	}

	closesocket(s);
	Sleep(1000);

	if(addDeleteProcessNewMessageCallback!=NULL)
	{
		addDeleteProcessNewMessageCallback->join();
		delete addDeleteProcessNewMessageCallback;
	}
	if(addDeleteProcessErrorCallback!=NULL)
	{
		addDeleteProcessErrorCallback->join();
		delete addDeleteProcessErrorCallback;
	}
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
	char bOptVal = 1;
	int result = setsockopt(s, SOL_SOCKET, TCP_NODELAY, (char *) &bOptVal, 1);

	sendNewMessage(0x0001,std::vector<char>());
}


void Client::sendError(int errCode,string errMessage)
{
	errorQueueMutex.lock();
	errorQueue.push_back(error(errCode,errMessage));
	errorQueueMutex.unlock();
}

void Client::sendNewMessage(short id,vector<char> data)
{
	newMessageQueueMutex.lock();
	newMessageQueue.push_back(newMessage(id,data));
	newMessageQueueMutex.unlock();
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
			static vector<char> buffer_ = vector<char>();
			static char buffer[512];
			static short currPos = 0;
			static short nextMsgSize = 0;
			
			Sleep(1);

			int recievedBytes = recv(s,buffer,512,0);
			if(recievedBytes == 0)
				break;//Connection closed
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

			for(int i=0;i<recievedBytes;i++)
				buffer_.push_back(buffer[i]);
			
			currPos += recievedBytes;
			while (currPos >= nextMsgSize && currPos != 0)
			{
				if (nextMsgSize < 2)
					nextMsgSize = (buffer_[0]<<8)+buffer_[1];
				else
				{
					currPos -= nextMsgSize;
					short id = (buffer_[2]<<8) + buffer_[3];

					vector<char> message;//RECIEVE MAL MACHEN
					if(nextMsgSize>4)
						message.insert(message.end(),buffer_.begin()+4,buffer_.begin()+nextMsgSize);

					buffer_.erase(buffer_.begin(),buffer_.begin()+nextMsgSize);

					sendNewMessage(id,message);

					nextMsgSize = 1;
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