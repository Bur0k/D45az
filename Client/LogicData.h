#ifndef LOGICDATA_H
#define LOGICDATA_H

#include "NetworkParticipant.h"
#include "Client.h"

class LogicData : public NetworkParticipant
{
private:

	Client* c;

public:
	LogicData();
	~LogicData();

	void processNewMessage(short id,vector<char> data);
	void processNetworkError(int id, std::string msg);
};

#endif