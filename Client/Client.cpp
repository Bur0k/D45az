#include "Client.h"

#include <vld.h>

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
	newMessageCallbackMutex.lock();
	newMessageCallback.push_back(np);
	newMessageCallbackMutex.unlock();
}

void Client::deleteFromNewMessageCallback(NetworkParticipant* np)
{
	newMessageCallbackMutex.lock();
	for(unsigned int i=0;i<newMessageCallback.size();i++)
		if(newMessageCallback[i] == np)
		{
			newMessageCallback.erase(newMessageCallback.begin()+i);
			break;
		}
	newMessageCallbackMutex.unlock();
}

void Client::addToErrorCallback(NetworkParticipant* np)
{
	errorCallbackMutex.lock();
	errorCallback.push_back(np);
	errorCallbackMutex.unlock();
}

void Client::deleteFromErrorCallback(NetworkParticipant* np)
{
	errorCallbackMutex.lock();
	for(unsigned int i=0;i<errorCallback.size();i++)
		if(errorCallback[i] == np)
		{
			errorCallback.erase(errorCallback.begin()+i);
			break;
		}
	errorCallbackMutex.unlock();
}