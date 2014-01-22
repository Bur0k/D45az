#ifndef CONNECT_H
#define CONNECT_H

#include "NetworkParticipant.h"
#include "Client.h"
#include <vector>
#include <atomic>

class Connect : public NetworkParticipant
{
	Client* c;
	std::atomic<short> state;
	std::atomic<string*> errorMsg;

public:
	Connect();
	~Connect();

	//returns 0 for no Response until now, returns 1 a succesfull connection, returns -1 if there is an error
	std::string getErrorMsg(){return *(errorMsg.operator std::string *());}
	short getState();
	void processNewMessage(short id,vector<char> data);
	void processNetworkError(int id, std::string msg);
};

#endif