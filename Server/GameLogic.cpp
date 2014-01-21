#include "GameLogic.h"

GameLogic::GameLogic(vector<PlayerData*> players, Map* map)
{
	this->server = Server::get();

	server->addToNewMessageCallback(this);
	server->addToErrorCallback(this);

	this->map = map;

	MapLayer* v = this->map->layers[0];
	MapLayer* w = this->map->layers[0];
	int id = 1;

	for( int i = 0; i < map->layers.size();i++)
		if(map->layers[i]->isCityLayer)
			v = map->layers[i];
		else if(map->layers[i]->isBarricadeLayer)
			w = map->layers[i];
	
	for( int i = 0; i < v->layer.size();i++)
		for( int j = 0; j < v->layer[i].size();j++)
		{
			if( v->layer[i][j] == STARTCITY)
			{
				CityLogic* c = new CityLogic(id, i, j);
				this->startCities.push_back(c);
				id++;
			}
			else if( v->layer[i][j] == NEUTRALCITY)
			{
				CityLogic* c = new CityLogic(id, i, j);
				this->neutralCities.push_back(c);
				id++;
			}
		}

	for(int i = 0; i < w->layer.size(); i++)
		for(int j = 0; j < w->layer[i].size(); j++)
		{
			if(w->layer[i][j] == BARRICADE1 || w->layer[i][j] == BARRICADE2 || w->layer[i][j] == STARTCITY || w->layer[i][j] == NEUTRALCITY)
			{
				POINT* p = new POINT();
				p->x = j;
				p->y = i;
				this->barricades.push_back(p);
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

	for(int i = 0; i < this->neutralCities.size(); i++)
		delete this->neutralCities[i];

	for(int i = 0; i < this->barricades.size(); i++)
		delete this->barricades[i];

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