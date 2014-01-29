#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "NetworkParticipant.h"
#include "Server.h"
#include "IngameLogic.h"
#include "Map.h"
#include "CityLogic.h"
#include <vector>
#include <math.h>

using namespace std;


#define STARTCITY 51
#define NEUTRALCITY 49
#define BARRICADE1 13
#define BARRICADE2 10


class GameLogic : public NetworkParticipant
{
private:
	Server* server;

	vector<IngameLogic*> playersIngame;
	Map* map;
	vector<CityLogic*> startCities;
	vector<CityLogic*> neutralCities; 

public:
	GameLogic::GameLogic(vector<PlayerData*> players, Map* map);
	GameLogic::~GameLogic();

	void processNewMessage(SOCKET s,short id,std::vector<char> data);
	void processNetworkError(SOCKET s,int errCode,std::string errMessage);
};

#endif