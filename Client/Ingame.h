#ifndef INGAME_H
#define INGAME_H

#include "NetworkParticipant.h"
#include "Client.h"

class Ingame : public NetworkParticipant
{
private:

	Client* c;

public:
	Ingame();
	~Ingame();

	void processNewMessage(short id,vector<unsigned char> data);
	void processNetworkError(int id, std::string msg);
};

#endif