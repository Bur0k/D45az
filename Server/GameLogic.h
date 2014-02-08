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
#include <sstream>


using namespace std;


//#define STARTCITY 53
//#define NEUTRALCITY 45

static const int STARTCITY = 53;
static const int NEUTRALCITY = 45;

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
	GameLogic::GameLogic(vector<PlayerData> players, Map* map);
	GameLogic::~GameLogic();

	void computeTurns();
	void isCollision(POINT* pos, vector<UnitGroupLogic*> armies);
	vector<unsigned char> divideForMessage(int number);

	void processNewMessage(SOCKET s,short id,std::vector<unsigned char> data);
	void processNetworkError(SOCKET s,int errCode,std::string errMessage);
	UnitGroupLogic fight(UnitGroupLogic army1, UnitGroupLogic army2);
};

#endif