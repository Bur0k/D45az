#ifndef GAMELOBBYLOGIC_H
#define GAMELOBBYLOGIC_H

#include <vector>
#include "PlayerData.h"
#include "Server.h"
#include "NetworkParticipant.h"

using namespace std;

class GameLobbyLogic : public NetworkParticipant
{
private:
	Server* server;
	short id;
	vector<PlayerData*> players;
	short playerlimit;
	PlayerData gameMaster;
	//Map currentMap;

public:
	GameLobbyLogic(short id, PlayerData master);
	~GameLobbyLogic();

	/*GETTER - SETTER*/

	void setID(short id);
	short getID();
	void setPlayerlimit(short limit);
	short getPlayerlimit();
	void setGamemaster(PlayerData player);
	PlayerData getGamemaster();
	vector<PlayerData*>& getPlayers(); 
	/*void setMap(Map map);*/
	/*Map getMap();*/

	/*Funktionen*/

	void addPlayer(PlayerData* player);
	void sendPlayerNames(SOCKET s);
	void sendMaxPlayers(SOCKET s);
	void sendGameMaster(SOCKET s);
	void sendCurrentMap(SOCKET s);

	/*Kommunikation*/

	void processNewMessage(SOCKET s,short id,std::vector<char> data);
	void processNetworkError(SOCKET s,int errCode,std::string errMessage);
};

#endif