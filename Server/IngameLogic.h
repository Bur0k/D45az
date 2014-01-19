#ifndef INGAMELOGIC_H
#define INGAMELOGIC_H

#include "NetworkParticipant.h"
#include "Server.h"
#include "PlayerData.h"
#include "CityLogic.h"
#include "UnitGroupLogic.h"
#include <vector>

using namespace std;

class IngameLogic : public NetworkParticipant
{
private:
	Server* server;

	PlayerData* owner;
	vector<CityLogic> cities;
	vector<UnitGroupLogic*> unitGroups;
	int gold;

public:
	IngameLogic::IngameLogic(PlayerData* owner);
	IngameLogic::~IngameLogic();

	//Funktionen

	void processNewMessage(SOCKET s,short id,std::vector<char> data);
	void processNetworkError(SOCKET s,int errCode,std::string errMessage);
};

#endif