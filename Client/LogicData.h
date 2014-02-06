#ifndef LOGICDATA_H
#define LOGICDATA_H

#include "NetworkParticipant.h"
#include "Client.h"
#include "Ingame.h"
#include "City.h"
#include "UnitGroup.h"
#include <string>
#include <SFML\Graphics.hpp>
#include <sstream>

class LogicData : public NetworkParticipant
{
private:

	Client* c;

public:

	vector<string> playersIngame;
	vector<City*> allCities;
	vector<City*> ownedCities;
	vector<UnitGroup*> allUnits;
	vector<UnitGroup*> ownedUnits;
	int gold;
	bool serverReady;

	LogicData();
	~LogicData();

	// Funktionen

	void updateGameData();
	void requestPlayers();
	void requestAllCities();
	void requestOwnedCities();
	void requestAllUnits();
	void requestOwnedUnits();
	void requestGold();

	void processNewMessage(short id,vector<char> data);
	void processNetworkError(int id, std::string msg);
};

#endif