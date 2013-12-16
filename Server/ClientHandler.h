#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <list>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

class ClientHandler
{
	thread* recieveThread;

	void beginRecieve();
	void sendNewMessage(ClientHandler* ch,short id,vector<char> data);
	void sendError(ClientHandler* ch,int errCode,string errMessage);

	vector<void (*)(ClientHandler* ch,short id,vector<char> data)>* newMessageCallback;
	vector<void (*)(ClientHandler* ch,int errCode,string errMessage)>* errorCallback;
	
	vector<thread*> writeThreads;
	mutex writeThreadsMutex;
	mutex writeMutex;
	bool running;
public:
	bool readyToDelete;
	SOCKET s; // Die eindeutige ID des Clienten für diesen Zeitpunkt bis zum nächsten Disconnet dieses Objektes
	ClientHandler(SOCKET S,vector<void (*)(ClientHandler* ch,short id,vector<char> data)>* NewMessageCallback,
		vector<void (*)(ClientHandler* ch,int errCode,string errMessage)>* ErrorCallback);
	~ClientHandler();
	void write(short id, vector<char>data);
};

#endif