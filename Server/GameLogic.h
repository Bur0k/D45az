#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "NetworkParticipant.h"
#include "Server.h"
#include "IngameLogic.h"
#include "Map.h"
#include "CityLogic.h"
#include <vector>
#include <math.h>
#include "pArmy.h"


using namespace std;


#define STARTCITY 53
#define NEUTRALCITY 49

class GameLogic : public NetworkParticipant
{
private:
	Server* server;

	vector<pArmy*> movingArmies;
	vector<IngameLogic*> playersIngame;
	vector<CityLogic*> startCities;
	vector<CityLogic*> neutralCities;
	short playerCommits;
	Map* map;

public:
	GameLogic::GameLogic(vector<PlayerData*> players, Map* map);
	GameLogic::~GameLogic();

	void computeTurns();
	void isCollision(POINT* pos, vector<UnitGroupLogic*> armies);

	void processNewMessage(SOCKET s,short id,std::vector<char> data);
	void processNetworkError(SOCKET s,int errCode,std::string errMessage);
};

#endif