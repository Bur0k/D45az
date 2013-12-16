#ifndef LOBBYLOGIC_H
#define LOBBYLOGIC_H

#include <vector>
#include <map>
#include "ClientHandler.h"
#include "Server.h"
#include "GameLobbyLogic.h"

class LobbyLogic
{
private:
	map<short, GameLobbyLogic> gamesCreated;

public:
	LobbyLogic();
	~LobbyLogic();
};

#endif