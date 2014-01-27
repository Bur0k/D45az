#ifndef _GAMELOBBY_H
#define _GAMELOBBY_H

#include "Client.h"
#include "NetworkParticipant.h"
#include <atomic>

class GameLobby : public NetworkParticipant
{
private:

	Client* c;

public:
	vector<string> players;
	short playerLimit;
	string gameMaster;
	std::atomic<short> updated;//Bit 0 = players, 1=playerLimit,2=gameMaster
	//Map current Map;

private:
	bool Ingame;
	bool disconnected;

public:
	GameLobby();
	~GameLobby();

	void processNewMessage(short id,vector<char> data);
	void processNetworkError(int id, std::string msg);

	// Funktionen

	void disconnect();
	void startGame();
	void mapChange(short mapID);
	void maxPlayerChange(short value);
};

#endif