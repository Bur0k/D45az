#ifndef CITYLOGIC_H
#define CITYLOGIC_H

#include "NetworkParticipant.h"
#include "Server.h"
#include <vector>

using namespace std;

class CityLogic : public NetworkParticipant
{
private:
	Server* server;

	short id;
	POINT* position;
	int level;
	int generatedIncome;

public:
	CityLogic(short id, short x, short y);
	~CityLogic();
	
	// Funktionen

	void upgradeCity();

	void processNewMessage(SOCKET s,short id,std::vector<char> data);
	void processNetworkError(SOCKET s,int errCode,std::string errMessage);
};

#endif