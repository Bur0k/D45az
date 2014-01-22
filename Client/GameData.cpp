#include "GameData.h"

GameData::GameData()
{
}

GameData::~GameData()
{
}

void GameData::processNewMessage(short id,vector<char> data)
{
	switch(id)
	{
	case 0x0:
		{

		}break;
	}
}

void GameData::processNetworkError(int id, std::string msg)
{

}