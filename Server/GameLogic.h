#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "NetworkParticipant.h"
#include "Server.h"
#include "IngameLogic.h"
#include <vector>

using namespace std;

class GameLogic : public NetworkParticipant
{
private:
	Server* server;

	vector<IngameLogic> playersIngame;

public:
	GameLogic::GameLogic(vector<PlayerData*> players, short mapID);
	GameLogic::~GameLogic();

	void processNewMessage(SOCKET s,short id,std::vector<char> data);
	void processNetworkError(SOCKET s,int errCode,std::string errMessage);
};

#endif