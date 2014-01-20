#ifndef UNITLOGIC_H
#define UNITLOGIC_H

#include "NetworkParticipant.h"
#include "Server.h"

using namespace std;

class UnitLogic : public NetworkParticipant
{
private:
	Server* server;

public:
	UnitLogic(short type);
	~UnitLogic();

	int attackpower;
	int range;

	void processNewMessage(SOCKET s,short id,std::vector<char> data);
	void processNetworkError(SOCKET s,int errCode,std::string errMessage);

};

#endif