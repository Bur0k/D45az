#include "GameLobby.h"

GameLobby::GameLobby()
{
	c = Client::get();
	c->addToNewMessageCallback(this);

	this->Ingame = false;
	this->disconnected = false;

	updated = 0;

	vector<char> erfg;
	this->c->write(0x0330, erfg);
}

GameLobby::~GameLobby(void)
{
	c->deleteFromNewMessageCallback(this);
}

// Funktionen

void GameLobby::disconnect()
{
	vector<char> erfg;

	this->c->write(0x0300, erfg);
}

void GameLobby::startGame()
{
	vector<char> erfg;

	this->c->write(0x0303, erfg);
}

void GameLobby::mapChange(short mapID)
{
	vector<char> erfg = code(mapID);

	this->c->write(0x0310, erfg);
}

void GameLobby::maxPlayerChange(short value)
{
	vector<char> erfg = code(value);

	this->c->write(0x0311, erfg);
}

void GameLobby::kickPlayer(string name)
{
	vector<char> erfg = code((short) name.length());

	vector<char> tmp = code(name);
	for (unsigned int i = 0; i < name.length(); i++)
		erfg.push_back(tmp[i]);

	this->c->write(0x0312, erfg);
}

void GameLobby::processNewMessage(short id,vector<char> data)
{
	switch(id)
	{
	case 0x0301:
		{
			this->disconnected = true;
		}break;
	case 0x0302:
		{
			string name;
			players.clear();
			for(unsigned int i = 0; i < data.size(); i++)
			{
				if(data[i] != '/')
					name += data[i];
				else
				{
					this->players.push_back(name);
					name.clear();
				}
			}
			updated |= 1;
		}break;
	case 0x0304:
		{
			this->Ingame = true;
			updated |= 8;
		}break;
	case 0x0305:
		{
			this->playerLimit = data[0];
			updated |= 2;
		}break;
	case 0x0306:
		{
			this->gameMaster = decodeString(data, 0, data.size());
			updated |= 4;
		}break;
	case 0x0320:
		{
			// Mapchange
		}break;
	case 0x0321:
		{
			this->playerLimit = data[0];
			updated |= 2;
		}break;
	}
}

void GameLobby::processNetworkError(int id, std::string msg)
{
}