#ifndef LOBBYLOGIC_H
#define LOBBYLOGIC_H

#include <vector>
#include <map>
#include "Server.h"
#include "GameLobbyLogic.h"
#include "LogInLogic.h"
#include <string>
#include "NetworkParticipant.h"


class LobbyLogic : public NetworkParticipant
{
private:
	map<short, GameLobbyLogic*> gamesCreated;
	Server* server;


public:
	LobbyLogic();
	~LobbyLogic();

	void processNewMessage(SOCKET s,short id,std::vector<unsigned char> data);
	void processNetworkError(SOCKET s,int errCode,std::string errMessage);
};

#endif