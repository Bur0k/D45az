#ifndef UNITLOGIC_H
#define UNITLOGIC_H

#include "NetworkParticipant.h"
#include "Server.h"

using namespace std;

enum class UnitTypes{LIGHT, HEAVY, LONGRANGE, ARTILLERY};

class UnitLogic : public NetworkParticipant
{
private:
	Server* server;

public:
	UnitLogic(UnitTypes type);
	~UnitLogic();

	int attackpower;
	int range;
	UnitTypes type;

	void processNewMessage(SOCKET s,short id,std::vector<char> data);
	void processNetworkError(SOCKET s,int errCode,std::string errMessage);

};

#endif