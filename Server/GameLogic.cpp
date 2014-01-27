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

	for(signed int i = 0; i < map->layers.size();i++)
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

	for(unsigned int i = 0; i < w->layer.size(); i++)
		for(unsigned int j = 0; j < w->layer[i].size(); j++)
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
	for(unsigned int i = 0; i < this->playersIngame.size(); i++)
		delete this->playersIngame[i];

	for(unsigned int i = 0; i < this->startCities.size(); i++)
		delete this->startCities[i];

	for(unsigned int i = 0; i < this->neutralCities.size(); i++)
		delete this->neutralCities[i];

	for(unsigned int i = 0; i < this->barricades.size(); i++)
		delete this->barricades[i];

	server->deleteFromNewMessageCallback(this);
	server->deleteFromErrorCallback(this);
}

void GameLogic::processNewMessage(SOCKET s,short id,std::vector<char> data)
{
	std::vector<char> erfg;

	switch(id)
	{
		case 0x0400:
			{
				for(int i = 0; i < (signed) this->playersIngame.size(); i++)
				{
					string name = this->playersIngame[i]->owner->Name;
					vector<char> tmp = code(name);

					erfg.insert(erfg.end(), tmp.begin(), tmp.end());
					erfg.push_back('/');
				}

				server->write(s, 0x0401, erfg);
			}break;
		case 0x0402:
			{
				int length = this->neutralCities.size() + this->startCities.size();

				erfg.push_back(length);

				for(unsigned int i = 0; i < this->neutralCities.size(); i++)
				{
					erfg.push_back(this->neutralCities[i]->position->x);
					erfg.push_back(this->neutralCities[i]->position->y);
					erfg.push_back(this->neutralCities[i]->level);
				}
				for(unsigned int i = 0; i < this->startCities.size(); i++)
				{
					erfg.push_back(this->startCities[i]->position->x);
					erfg.push_back(this->startCities[i]->position->y);
					erfg.push_back(this->startCities[i]->level);
				}

				server->write(s, 0x0403, erfg);
			}break;
		case 0x0404:
			{
				int index;

				for(int i = 0; i < this->playersIngame.size(); i++)
				{
					if(this->playersIngame[i]->owner->s == s)
						index = i;
				}

				int length = this->playersIngame[index]->cities.size();

				erfg.push_back(length);

				for(int i = 0; i < this->playersIngame[index]->cities.size(); i++)
				{
					erfg.push_back(this->playersIngame[index]->cities[i]->position->x);
					erfg.push_back(this->playersIngame[index]->cities[i]->position->y);
					erfg.push_back(this->playersIngame[index]->cities[i]->level);
				}

				server->write(s, 0x0405, erfg);
			}break;
		case 0x0406:
			{
				for(int i = 0; i < this->barricades.size(); i++)
				{
					erfg.push_back(this->barricades[i]->x);
					erfg.push_back(this->barricades[i]->y);
				}

				server->write(s, 0x0407, erfg);
			}break;
	}
}
	
void GameLogic::processNetworkError(SOCKET s,int errCode,std::string errMessage)
{

}