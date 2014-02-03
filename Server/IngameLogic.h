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
public:
	Server* server;

	short player_ID;
	PlayerData* owner;
	vector<CityLogic*> cities;
	vector<UnitGroupLogic*> unitGroups;
	int gold;

public:
	IngameLogic::IngameLogic(int id, PlayerData* owner, CityLogic* startCity);
	IngameLogic::~IngameLogic();

	//Funktionen

	void processNewMessage(SOCKET s,short id,std::vector<char> data);
	void processNetworkError(SOCKET s,int errCode,std::string errMessage);
};

#endif