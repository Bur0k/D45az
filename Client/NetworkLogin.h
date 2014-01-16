#ifndef _NETWORKLOGIN_H
#define _NETWORKLOGIN_H

#include "NetworkParticipant.h"
#include "Client.h"
#include <vector>
#include <atomic>

class NetworkLogin : public NetworkParticipant
{
	Client* c;
	std::atomic<short> state;

public:
	NetworkLogin(string Name);
	~NetworkLogin();

	//returns 0 for no Response until now, returns 1 for name can be used returns -1 for name is already used
	short getState();
	void processNewMessage(short id,vector<char> data);
	void processNetworkError(int id, std::string msg);
};

#endif