#ifndef GAMELOBBYLOGIC_H
#define GAMELOBBYLOGIC_H

#include <vector>
#include "PlayerData.h"
#include "Server.h"
#include "NetworkParticipant.h"
#include "GameLogic.h"
#include "Map.h"

using namespace std;

class GameLobbyLogic : public NetworkParticipant
{
private:
	Server* server;
	//short id;
	vector<PlayerData> players;
	GameLogic* game;
	short playerlimit;
	PlayerData gameMaster;
	string gameLobbyName;
	short mapID;
	Map* currentMap;

public:
	GameLobbyLogic(short id, PlayerData master, string gameLobbyName);
	~GameLobbyLogic();

	/*GETTER - SETTER*/
	void setName(string name);
	string getName();
	//void setID(short id);
	//short getID();
	void setPlayerlimit(short limit);
	short getPlayerlimit();
	void setGamemaster(PlayerData player);
	PlayerData getGamemaster();
	vector<PlayerData>& getPlayers(); 
	void setMap(Map* map);
	Map* getMap();

	/*Funktionen*/

	void addPlayer(PlayerData player);
	bool isAlreadyConnected(SOCKET s);
	void sendPlayerNames(SOCKET s);
	void sendMaxPlayers(SOCKET s);
	void sendGameMaster(SOCKET s);
	void sendCurrentMap(SOCKET s);
	void sendGameLobbyData(SOCKET s);

	/*Kommunikation*/

	void processNewMessage(SOCKET s,short id,std::vector<unsigned char> data);
	void processNetworkError(SOCKET s,int errCode,std::string errMessage);
};

#endif