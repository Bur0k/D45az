#ifndef GAMELOBBYLOGIC_H
#define GAMELOBBYLOGIC_H

#include <vector>
#include "User.h"
#include "Server.h"

using namespace std;

class GameLobbyLogic
{
private:
	Server* server;
	short id;
	vector<User*> players;
	short playerlimit;
	User* gameMaster;
	/*Map currentMap;*/

public:
	GameLobbyLogic(short id, User* master);
	~GameLobbyLogic();
	
	/*GETTER - SETTER*/

	void setID(short id);
	short getID();
	void setPlayerlimit(short limit);
	short getPlayerlimit();
	void setGamemaster(User* player);
	User* getGamemaster();
	/*void setMap(Map map);*/
	/*Map getMap();*/

	/*Kommunikation*/

	void LogicMessageCallback(SOCKET s,short id,vector<char> data);
};

#endif