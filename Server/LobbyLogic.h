#ifndef LOBBYLOGIC_H
#define LOBBYLOGIC_H

#include <vector>
#include <map>
#include "Server.h"
#include "GameLobbyLogic.h"


// MUSS MAL IRGENDWO ANGELEGT WERDEN


class LobbyLogic
{
private:
	map<short, GameLobbyLogic> gamesCreated;

public:
	LobbyLogic();
	~LobbyLogic();

	void LobbyLogicMessageCallback(SOCKET s,short id,vector<char> data);
};

#endif