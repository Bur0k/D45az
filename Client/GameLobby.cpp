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
			string name;

			for(int i = 0; i > data.size(); i++)
			{
				while(data[i] != '/')
					name += data[i];

				this->players.push_back(name);
			}
		}break;
	case 0x0304:
		{

		}break;
	case 0x0305:
		{

		}break;
	case 0x0306:
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