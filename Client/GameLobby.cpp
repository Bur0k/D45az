#include "GameLobby.h"


GameLobby::GameLobby(void)
{
}


GameLobby::~GameLobby(void)
{
}

void GameLobby::processNewMessage(SOCKET s,short id,std::vector<char> data)
{
	switch(id)
	{
	case 0x0301:
		{

		}break;
	case 0x0302:
		{

		}break;
	case 0x0304:
		{

		}break;
	case 0x0320:
		{

		}break;
	case 0x0321:
		{

		}break;
	}
}