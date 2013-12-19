#ifndef CLIENT_H
#define CLIENT_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <list>
#include <vector>
#include <thread>
#include <mutex>
#include "NetworkParticipant.h"

using namespace std;

//CLIENT SOLLTE EIN LEERPAKET SCHICKEN VOR DER KOMMUNIKATION!
//CLIENT BEKOMMT DANN AUCH NOCH EIN LEERPAKET 
class Client
{
	SOCKET s;

	void sendError(int errCode,string errMessage);
	void sendNewMessage(short id,vector<char> data);
	vector<NetworkParticipant*> errorCallback;
	vector<NetworkParticipant*> newMessageCallback;
	mutex newMessageCallbackMutex;
	mutex errorCallbackMutex;

	bool runRead;

	thread* readThread;

	vector<thread*> writeThreads;
	mutex writeThreadsMutex;

	mutex writeMutex;
	
	static Client* self;
	Client();

public:
	static Client* get()
	{
		return self;
	}
	~Client();

	void connectToServer(string ip, int port);
	void write(short id, vector<char>data);
	void beginRead();
	void endRead();

	
	void addToNewMessageCallback(NetworkParticipant* np);
	void deleteFromNewMessageCallback(NetworkParticipant* np);
	void addToErrorCallback(NetworkParticipant* np);
	void deleteFromErrorCallback(NetworkParticipant* np);
};


#endif