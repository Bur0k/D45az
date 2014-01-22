#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "NetworkParticipant.h"
#include "Client.h"

class GameData : public NetworkParticipant
{
private:

	Client* c;

public:
	GameData();
	~GameData();

	void processNewMessage(short id,vector<char> data);
	void processNetworkError(int id, std::string msg);
};

#endif