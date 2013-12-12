#ifndef CLIENT_H
#define Server_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <list>
#include <vector>
#include <thread>
#include <mutex>
#include "ClientHandler.h"

using namespace std;


class Server
{
	long rc;
	SOCKET acceptSocket;
	SOCKADDR_IN addr;


	void sendError(ClientHandler* ch,int errCode,string errMessage);

	thread* acceptThread;
	bool runAccept;

	vector<ClientHandler*> clientHandler;
public:
	Server();
	~Server();

	void startListening();
	vector<void (*)(ClientHandler* ch,int errCode,string errMessage)> errorCallback;
	vector<void (*)(ClientHandler* ch,short id,vector<char> data)> newMessageCallback;
};


#endif