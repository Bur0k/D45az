#ifndef _LOBBY_H
#define _LOBBY_H

#include "NetworkParticipant.h"
#include "Client.h"
#include <vector>

class Lobby : public NetworkParticipant
{
	Client* c;
	string name;
	

public:
	Lobby(string name);
	~Lobby();

	void connectToGameLobby(char mapid);
	void createNewGameLobby();
	void askforLobbyData();
	void processNewMessage(short id,vector<char> data);
	void processNetworkError(int id, std::string msg);
};

#endif