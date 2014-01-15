#ifndef _LOBBY_H
#define _LOBBY_H

#include "NetworkParticipant.h"
#include "Client.h"
#include "PlayerData.h"
#include "GameLobby.h"
#include <vector>
#include <map>

class Lobby : public NetworkParticipant
{
	Client* c;
	string name;
	map<char, GameData> gamesCreated;
	
public:
	GameLobby* gameLobby;

	Lobby(string name);
	~Lobby();

	void connectToGameLobby(char mapid);
	void createNewGameLobby();
	void askforLobbyData();
	void processNewMessage(short id,vector<char> data);
	void processNetworkError(int id, std::string msg);
};

#endif