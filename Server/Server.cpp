#include "Server.h"

#include <vld.h>

Server::Server()
{
}

Server::~Server()
{
	runAccept = false;
	if(acceptThread!=NULL)
	{
		acceptThread->join();
		delete acceptThread;
	}
	for(int i=0;i<clientHandler.size();i++)
		delete clientHandler[i];
}

void Server::startListening()
{
	WSADATA wsa;

	if(WSAStartup(MAKEWORD(2,0),&wsa))
	{
		sendError(NULL,-4,"WSAStartup failed: "+to_string(WSAGetLastError()));
		return ;
	}

	acceptSocket=socket(AF_INET,SOCK_STREAM,0);
	if(acceptSocket==INVALID_SOCKET)
	{
		sendError(NULL,-1,"Socket could not be created: "+to_string(WSAGetLastError()));
		return ;
	}

	memset(&addr,0,sizeof(SOCKADDR_IN));
	addr.sin_family=AF_INET;
	addr.sin_port=htons(4242);
	addr.sin_addr.s_addr=INADDR_ANY; // gewisse compiler brauchen hier ADDR_ANY
	rc=::bind(acceptSocket,(SOCKADDR*)&addr,sizeof(SOCKADDR_IN));
	if(rc==SOCKET_ERROR)
	{
		sendError(NULL,-2,"Socket could not be bound to Port 424242: "+to_string(WSAGetLastError()));
		return ;
	}

	// In den listen Modus
	rc=listen(acceptSocket,100);
	if(rc==SOCKET_ERROR)
	{
		sendError(NULL,-3,"Socket could not Listen: "+to_string(WSAGetLastError()));
		return ;
	}

	u_long nonBlockMode = 1;
	rc = ioctlsocket(acceptSocket, FIONBIO, &nonBlockMode);
	if (rc != NO_ERROR)
	{
		sendError(NULL,-5,"Could not set Non-Blocking mode: "+to_string(WSAGetLastError()));
		return ;
	}

	runAccept = true;
	acceptThread = new thread([&]
	{
		while(runAccept)
		{
			int size = sizeof(SOCKADDR_IN);
			SOCKET s = accept(acceptSocket,(sockaddr*)&addr,&size);
			if(s!=INVALID_SOCKET)
			{
				clientHandler.push_back(new ClientHandler(s,&newMessageCallback,&errorCallback));
			}
			for(unsigned int i=0;i<clientHandler.size();)
			{
				if(clientHandler[i]->readyToDelete == true)
				{
					delete clientHandler[i];
					clientHandler.erase(clientHandler.begin()+i);
				}
				else
					i++;
			}
			Sleep(1);
		}
	});
}

void Server::sendError(ClientHandler* ch,int errCode,string errMessage)
{
	for(unsigned int i=0;i<errorCallback.size();i++)
		errorCallback[i](ch,errCode,errMessage);
}