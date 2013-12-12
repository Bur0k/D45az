#include "Server.h"

#include <vld.h>

Server::Server()
{
}

Server::~Server()
{
}

void Server::startListening()
{
	WSADATA wsa;

	if(WSAStartup(MAKEWORD(2,0),&wsa))
	{
		sendError(-4,"WSAStartup failed: "+to_string(WSAGetLastError()));
		return ;
	}

	acceptSocket=socket(AF_INET,SOCK_STREAM,0);
	if(acceptSocket==INVALID_SOCKET)
	{
		sendError(-1,"Socket could not be created: "+to_string(WSAGetLastError()));
		return ;
	}

	memset(&addr,0,sizeof(SOCKADDR_IN));
	addr.sin_family=AF_INET;
	addr.sin_port=htons(424242);
	addr.sin_addr.s_addr=INADDR_ANY; // gewisse compiler brauchen hier ADDR_ANY
	rc=::bind(acceptSocket,(SOCKADDR*)&addr,sizeof(SOCKADDR_IN));
	if(rc==SOCKET_ERROR)
	{
		sendError(-2,"Socket could not be bound to Port 424242: "+to_string(WSAGetLastError()));
		return ;
	}

	// In den listen Modus
	rc=listen(acceptSocket,100);
	if(rc==SOCKET_ERROR)
	{
		sendError(-3,"Socket could not Listen: "+to_string(WSAGetLastError()));
		return ;
	}

	runAccept = true;
	acceptThread = new thread([&]
	{
		while(runAccept)
		{
			int size = sizeof(SOCKADDR_IN);
			SOCKET s = accept(acceptSocket,(sockaddr*)&addr,&size);
			while(false);
		}
	});
}

void Server::sendError(int errCode,string errMessage)
{
	for(unsigned int i=0;i<errorCallback.size();i++)
		errorCallback[i](errCode,errMessage);
}

void Server::sendNewMessage(short id,vector<char> data)
{
	for(unsigned int i=0;i<newMessageCallback.size();i++)
		newMessageCallback[i](id,data);
}