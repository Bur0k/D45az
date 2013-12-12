#include "ClientHandler.h"

ClientHandler::ClientHandler(SOCKET S,vector<void (*)(ClientHandler* ch,short id,vector<char> data)>* NewMessageCallback,
							 vector<void (*)(ClientHandler* ch,int errCode,string errMessage)>* ErrorCallback)
							 :s(S),running(true),newMessageCallback(NewMessageCallback),errorCallback(ErrorCallback),
							 readyToDelete(false)
{
	beginRecieve();
}

ClientHandler::~ClientHandler()
{
	running = false;
	for (unsigned int i = 0; i < writeThreads.size(); i++)
	{
		writeThreads[i]->join();
		delete writeThreads[i];
	}
	closesocket(s);

	recieveThread->join();
	delete recieveThread;
}

void ClientHandler::beginRecieve()
{
	recieveThread = new thread([=]()
	{
		while(running)
		{
			static char buffer[1024];
			static short currPos = 0;
			static short nextMsgSize = 0;

			Sleep(1);

			int recievedBytes = recv(s,buffer+currPos,1024-currPos,0);
			if(recievedBytes == 0)
			{
				running = false;
				sendNewMessage(this,2,vector<char>());
				break;
			}
			else if(recievedBytes <0)
			{
				if(WSAGetLastError() == 10035)//Would block
					continue;
				else//Anderer ECHTER Fehler
				{
					running = false;
					sendNewMessage(this,-1,vector<char>());
					sendError(this,-1,"recv fail: "+to_string(WSAGetLastError()));
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
					short id = (buffer[currPos+2]>>8) + buffer[currPos+3];

					char* msg = new char[nextMsgSize-4];
					memcpy(msg,buffer+currPos+4,sizeof(char)*(nextMsgSize-4));
					vector<char> message;
					for(int i=0;i<nextMsgSize-4;i++)
						message.push_back(msg[i]);

					sendNewMessage(this,id,message);


					nextMsgSize = 0;
					delete[] msg;
				}
			}
		}
	});
}



void ClientHandler::sendNewMessage(ClientHandler* ch, short id,vector<char> data)
{
	for(unsigned int i=0;i<newMessageCallback->size();i++)
		(*newMessageCallback)[i](ch,id,data);
}

void ClientHandler::write(short id, vector<char>data)
{
	thread* sendThread = new thread([=]()
	{
		vector<char> toSend(data);
		short size = (short) data.size()+4;//2byte länge, 2byte id

		toSend.insert(toSend.begin(),(char)id);
		toSend.insert(toSend.begin(),(char)(id>>8));

		toSend.insert(toSend.begin(),(char)size);
		toSend.insert(toSend.begin(),(char)(size>>8));

		char* buffer = new char[size];
		for(int i=0;i<size;i++)
			buffer[i]=toSend[i];

		writeMutex.lock();
		if (send(s,buffer,size,0) == SOCKET_ERROR)
			sendError(this,-3,"Send failed with error: "+to_string(WSAGetLastError()));
		writeMutex.unlock();

		delete[] buffer;
	});
	writeThreads.push_back(sendThread);
}

void ClientHandler::sendError(ClientHandler* ch,int errCode,string errMessage)
{
	for(unsigned int i=0;i<errorCallback->size();i++)
		(*errorCallback)[i](ch,errCode,errMessage);
	if(errCode == -1)
		readyToDelete=true;
}