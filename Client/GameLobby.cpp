#include "GameLobby.h"

GameLobby::GameLobby()
{
	c = Client::get();
	c->addToNewMessageCallback(this);

	this->Ingame = false;
	this->disconnected = false;

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
		}break;
	case 0x0304:
		{
			this->Ingame = true;
		}break;
	case 0x0305:
		{
			this->playerLimit = data[0];
		}break;
	case 0x0306:
		{
			this->gameMaster = decodeString(data, 0, data.size());
		}break;
	case 0x0320:
		{
			// Mapchange
		}break;
	case 0x0321:
		{
			this->playerLimit = data[0];
		}break;
	}
}

void GameLobby::processNetworkError(int id, std::string msg)
{
}