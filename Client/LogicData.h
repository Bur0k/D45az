#ifndef LOGICDATA_H
#define LOGICDATA_H

#include "NetworkParticipant.h"
#include "Client.h"
#include "Ingame.h"
#include "City.h"
#include "UnitGroup.h"
#include <string>
#include <SFML\Graphics.hpp>

class LogicData : public NetworkParticipant
{
private:

	Client* c;

	vector<string> playersIngame;
	vector<City*> allCities;
	vector<City*> ownedCities;
	vector<sf::Vector2i> barricades;
	vector<UnitGroup*> allUnits;
	vector<UnitGroup*> ownedUnits;

public:
	LogicData();
	~LogicData();

	// Funktionen

	void processNewMessage(short id,vector<char> data);
	void processNetworkError(int id, std::string msg);
};

#endif