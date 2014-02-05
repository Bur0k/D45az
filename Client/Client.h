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
#include <algorithm>
#include <iostream>

using namespace std;

//Lowbyte zuerst
std::vector<char> code(short s);
std::vector<char> code(int i);
std::vector<char> code(const std::string s);
short decodeShort(const std::vector<char>& v, int from);
int decodeInt(const std::vector<char>& v, int from);
std::string decodeString(const std::vector<char>& v, int from, int len);

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

	bool running;

	thread* readThread;

	thread* writeThread;
	list<vector<char>> toWrite;
	mutex toWriteMutex;

	thread* addNewMessageCallbackThread;
	vector<NetworkParticipant*> addNewMessageCallbackList;
	mutex addNewMessageCallbackMutex;
	thread* deleteNewMessageCallbackThread;
	vector<NetworkParticipant*> deleteNewMessageCallbackList;
	mutex deleteNewMessageCallbackMutex;

	thread* addErrorCallbackThread;
	vector<NetworkParticipant*> addErrorCallbackList;
	mutex addErrorCallbackMutex;
	thread* deleteErrorCallbackThread;
	vector<NetworkParticipant*> deleteErrorCallbackList;
	mutex deleteErrorCallbackMutex;


	mutex writeThreadsMutex;

	mutex writeMutex;
	
	static Client* self;
	Client();
	Client& Client::operator = (const Client& src)
	{
		return *this;      // Referenz zurückgeben
	}

public:
	static Client* get()
	{
		return self;
	}
	~Client();

	void connectToServer(string ip, int port);
	void write(short id, vector<char>data);
	void beginRead();

	
	void addToNewMessageCallback(NetworkParticipant* np);
	void deleteFromNewMessageCallback(NetworkParticipant* np);
	void addToErrorCallback(NetworkParticipant* np);
	void deleteFromErrorCallback(NetworkParticipant* np);
};


#endif