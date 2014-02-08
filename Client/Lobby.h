#ifndef _LOBBY_H
#define _LOBBY_H

#include "NetworkParticipant.h"
#include "Client.h"
#include "PlayerData.h"
#include "GameLobby.h"
#include <vector>
#include <map>
#include <atomic>

class Lobby : public NetworkParticipant
{
	Client* c;

	
public:
	mutex m;
	bool updated;
	bool inGameLobby;
	map<short, GameData> gamesCreated;


	//std::atomic<bool> gameLobby;

	Lobby();
	~Lobby();

	void connectToGameLobby(short mapid);
	void createNewGameLobby(std::string gamename);
	void askforLobbyData();
	void processNewMessage(short id,vector<unsigned char> data);
	void processNetworkError(int id, std::string msg);
};

#endif