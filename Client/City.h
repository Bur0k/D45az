#ifndef CITY_H
#define CITY_H

#include "NetworkParticipant.h"
#include "Client.h"

class City : public NetworkParticipant
{
private:

	Client* c;

public:
	City();
	~City();

	void processNewMessage(short id,vector<char> data);
	void processNetworkError(int id, std::string msg);
};

#endif