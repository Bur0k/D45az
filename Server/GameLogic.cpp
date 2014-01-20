#include "GameLogic.h"

GameLogic::GameLogic(vector<PlayerData*> players, Map* map)
{
	this->server = Server::get();

	server->addToNewMessageCallback(this);
	server->addToErrorCallback(this);

	this->map = map;

	MapLayer* v = this->map->layers[0];	
	int id = 1;

	for( int i = 0; i < map->layers.size();i++)
		if(map->layers[i]->isCityLayer)
			v = map->layers[i];
	
	for( int i = 0; i < v->layer.size();i++)
		for( int j = 0; j < v->layer[i].size();j++)
		{
			if( v->layer[i][j] == 51)
			{
				CityLogic* c = new CityLogic(id, i, j);
				this->startCities.push_back(c);
				id++;
			}
		}

	for(unsigned int i = 0; i < players.size(); i++)
	{
		IngameLogic* ingame = new IngameLogic(players[i], this->startCities[i]);
		this->playersIngame.push_back(ingame);
	}

	
}

GameLogic::~GameLogic()
{
	for(int i = 0; i < this->playersIngame.size(); i++)
		delete this->playersIngame[i];

	for(int i = 0; i < this->startCities.size(); i++)
		delete this->startCities[i];

	server->deleteFromNewMessageCallback(this);
	server->deleteFromErrorCallback(this);
}

void GameLogic::processNewMessage(SOCKET s,short id,std::vector<char> data)
{
	switch(id)
	{
	case 0x0400:
		{

		}
	}
}
	
void GameLogic::processNetworkError(SOCKET s,int errCode,std::string errMessage)
{

}