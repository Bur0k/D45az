#ifndef CLIENT_H
#define CLIENT_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <list>
#include <vector>

using namespace std;


class Client
{
	SOCKET s;

	void sendError(int errCode,string errMessage);
	void sendNewMessage(short id,vector<char> data);
public:
	vector<void (*)(int errCode,string errMessage)> errorCallback;
	vector<void (*)(short id,vector<char> data)> newMessageCallback;

	Client();

	void connectToServer(string ip, int port);
	void write(short id, vector<char>data);
	void beginRead();
};


#endif