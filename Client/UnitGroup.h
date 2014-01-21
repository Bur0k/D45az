#ifndef UNITGROUP_H
#define UNITGROUP_H

#include "NetworkParticipant.h"
#include "Client.h"

class UnitGroup : public NetworkParticipant
{
private:

	Client* c;

public:
	UnitGroup();
	~UnitGroup();

	void processNewMessage(short id,vector<char> data);
	void processNetworkError(int id, std::string msg);
};

#endif