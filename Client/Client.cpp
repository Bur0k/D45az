#include "Client.h"

#include <vld.h>

Client::Client()
{
	readThread = NULL;
}

Client::~Client()
{
	for (int i = 0; i < writeThreads.size(); i++)
	{
		writeThreads[i]->join();
		delete writeThreads[i];
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
}


void Client::sendError(int errCode,string errMessage)
{
	for(unsigned int i=0;i<errorCallback.size();i++)
		errorCallback[i](errCode,errMessage);
}

void Client::sendNewMessage(short id,vector<char> data)
{
	for(unsigned int i=0;i<newMessageCallback.size();i++)
		newMessageCallback[i](id,data);
}

void Client::write(short id, vector<char>data)
{
	thread* sendThread = new thread([=]()
	{
		vector<char> toSend(data);
		short size = (short) data.size()+4;//2byte l�nge, 2byte id

		toSend.insert(toSend.begin(),(char)id);
		toSend.insert(toSend.begin(),(char)(id>>8));

		toSend.insert(toSend.begin(),(char)size);
		toSend.insert(toSend.begin(),(char)(size>>8));

		char* buffer = new char[size];
		for(int i=0;i<size;i++)
			buffer[i]=toSend[i];

		writeMutex.lock();
		if (send(s,buffer,size,0) == SOCKET_ERROR)
			sendError(-3,"Send failed with error: "+to_string(WSAGetLastError()));
		writeMutex.unlock();

		delete[] buffer;
	});
	writeThreads.push_back(sendThread);
}

void Client::beginRead()
{
	runRead=true;
	if(readThread)
		return;
	readThread = new thread([=]()
	{
		while(runRead)
		{
			static char buffer[1024];
			static short currPos = 0;
			static short nextMsgSize = 0;

			int recievedBytes = recv(s,buffer+currPos,1024-currPos,0);
			currPos += recievedBytes;

			while (currPos >= nextMsgSize && currPos < 1)
			{
				if (nextMsgSize == 0)
					nextMsgSize = (buffer[0]<<8)+buffer[1];
				else
				{
					currPos -= nextMsgSize;
					short id = (buffer[currPos+2]>>8) + buffer[currPos+3];

					char* msg = new char[nextMsgSize];
					memcpy(msg,buffer+currPos+4,sizeof(char)*(nextMsgSize-4));
					vector<char> message;
					for(int i=0;i<nextMsgSize;i++)
						message.push_back(msg[i]);

					sendNewMessage(id,message);


					nextMsgSize = 0;
					delete[] msg;
				}
			}
			/*int recievedBytes = inputStream.read(currMsg, currPos, 512 - currPos);
			currPos += recievedBytes;

			while (currPos >= nextMsgSize && currPos != 0)
			{
			if (nextMsgSize == 0)
			nextMsgSize = (byte) currMsg[0];
			else
			{
			currPos -= nextMsgSize;
			byte[] msg = Arrays.copyOfRange(currMsg, currPos + 1, currPos + nextMsgSize);

			for (newMessageListener hl : listeners)
			hl.gotNewMessage(msg[0], Arrays.copyOfRange(msg, 1, msg.length));

			nextMsgSize = 0;
			}
			}*/
		}
	});
}

void Client::endRead()
{
	runRead=false;
}