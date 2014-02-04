#ifndef UNITLOGIC_H
#define UNITLOGIC_H

#define light 2.0
#define heavy 2.4
#define longrange 2.8
#define artillery 1.0

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

	UnitTypes type;
	short living;
	int attackpower;
	int range;

	void processNewMessage(SOCKET s,short id,std::vector<char> data);
	void processNetworkError(SOCKET s,int errCode,std::string errMessage);
};

#endif