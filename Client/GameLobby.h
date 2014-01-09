#ifndef _GAMELOBBY_H
#define _GAMELOBBY_H

#include "Client.h"

class GameLobby
{
private:

	Client* c;
	short id;

public:
	GameLobby(void);
	~GameLobby(void);

	void processNewMessage(SOCKET s,short id,std::vector<char> data);
	void processNetworkError(SOCKET s,int errCode,std::string errMessage);

	// Funktionen

	void disconnect();
	void startGame();
	void mapChange(short mapID);
	void maxPlayerChange(short value);
};

#endif