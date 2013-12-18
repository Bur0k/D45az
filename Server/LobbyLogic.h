#ifndef LOBBYLOGIC_H
#define LOBBYLOGIC_H

#include <vector>
#include <map>
#include "ClientHandler.h"
#include "Server.h"
#include "GameLobbyLogic.h"
#include <string>


// MUSS MAL IRGENDWO ANGELEGT WERDEN


class LobbyLogic
{
private:
	map<short, GameLobbyLogic*> gamesCreated;
	Server* server;

	static LobbyLogic* self;

public:

	LobbyLogic();
	~LobbyLogic();



	static void LobbyLogicMessageCallback(SOCKET s,short id,vector<char> data);
};

#endif