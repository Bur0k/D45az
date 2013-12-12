#ifndef CLIENT_H
#define Server_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <list>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;


class Server
{
	long rc;
	SOCKET acceptSocket;
	//SOCKET connectedSocket;
	SOCKADDR_IN addr;
	char buf[256];
	char buf2[300];
	// zusätzliche Variabeln
	FD_SET fdSet;
	int i;


	void sendError(int errCode,string errMessage);
	void sendNewMessage(short id,vector<char> data);

	thread* acceptThread;
	bool runAccept;
public:
	Server();
	~Server();

	void startListening();
	vector<void (*)(int errCode,string errMessage)> errorCallback;
	vector<void (*)(short id,vector<char> data)> newMessageCallback;
};


#endif