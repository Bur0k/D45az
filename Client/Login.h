#ifndef LOGIN_H
#define LOGIN_H

#include "NetworkParticipant.h"
#include "Client.h"
#include <vector>
#include <atomic>

class Login : public NetworkParticipant
{
	Client* c;
	std::atomic<short> state;

public:
	Login(string Name);
	~Login();

	//returns 0 for no Response until now, returns 1 for name can be used returns -1 for name is already used
	short getState();
	void processNewMessage(short id,vector<unsigned char> data);
	void processNetworkError(int id, std::string msg);
};

#endif