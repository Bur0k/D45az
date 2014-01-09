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

//Lowbyte zuerst
std::vector<char> code(short s)
{
	std::vector<char> v;
	v.push_back(s);
	v.push_back(s>>8);
	return v;
}
std::vector<char> code(int i)
{
	std::vector<char> v;
	v.push_back(i);
	v.push_back(i>>8);
	v.push_back(i>>16);
	v.push_back(i>>24);
	return v;
}
std::vector<char> code(const std::string s)
{
	std::vector<char> v;
	for_each(s.begin(),s.end(),[&](const char c){v.push_back(c);});
	return v;
}

//Lowbyte zuerst
short decodeShort(const std::vector<char>& v, int from)
{
	short s;
	s = v[from];
	s += v[from]<<8;
	return s;
}
int decodeInt(const std::vector<char>& v, int from)
{
	short i;
	i = v[from];
	i += v[from]<<8;
	i += v[from]<<16;
	i += v[from]<<24;
	return i;
}
std::string decodeString(const std::vector<char>& v, int from, int len)
{
	std::string s;
	for(int i=0;i<len;i++)
		s.push_back(v[from+i]);
	return s;
}


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

	
	void addToNewMessageCallback(NetworkParticipant* np);
	void deleteFromNewMessageCallback(NetworkParticipant* np);
	void addToErrorCallback(NetworkParticipant* np);
	void deleteFromErrorCallback(NetworkParticipant* np);
};


#endif