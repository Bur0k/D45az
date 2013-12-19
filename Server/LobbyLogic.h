#ifndef LOBBYLOGIC_H
#define LOBBYLOGIC_H

#include <vector>
#include <map>
#include "Server.h"
#include "GameLobbyLogic.h"
#include "LogInLogic.h"
#include <string>


// MUSS MAL IRGENDWO ANGELEGT WERDEN


class LobbyLogic
{
private:
	map<short, GameLobbyLogic*> gamesCreated;
	static LobbyLogic* self;
	Server* server;
	static LogInLogic* LogIn;

public:
	LobbyLogic();
	LobbyLogic(LogInLogic* l);
	~LobbyLogic();

	static void LobbyLogicMessageCallback(SOCKET s,short id,vector<char> data);
};

#endif