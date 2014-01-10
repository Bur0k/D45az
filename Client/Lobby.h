#ifndef _LOBBY_H
#define _LOBBY_H

#include "NetworkParticipant.h"
#include "Client.h"
#include "PlayerData.h"
#include <vector>
#include <map>

class CLobby : public NetworkParticipant
{
	Client* c;
	string name;
	map<char, GameData> gamesCreated;
	

public:
	CLobby(string name);
	~CLobby();

	void connectToGameLobby(char mapid);
	void createNewGameLobby();
	void askforLobbyData();
	void processNewMessage(short id,vector<char> data);
	void processNetworkError(int id, std::string msg);
};

#endif