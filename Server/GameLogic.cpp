#include "GameLogic.h"

GameLogic::GameLogic(vector<PlayerData*> players, Map* map)
{
	this->server = Server::get();

	server->addToNewMessageCallback(this);
	server->addToErrorCallback(this);

	this->map = map;

	MapLayer* v = this->map->layers[0];
	int id = 1;

	for(unsigned int i = 0; i < map->layers.size();	i++)
		if(map->layers[i]->isCityLayer)
			v = map->layers[i];
	
	for(unsigned int i = 0; i < v->layer.size(); i += 2)
		for(unsigned int j = 0; j < v->layer[i].size(); i += 2)
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

	for(unsigned int i = 0; i < players.size(); i++)
	{
		this->startCities[i]->player_ID = i;
	}

	for(unsigned int i = 0; i < players.size(); i++)
	{
		IngameLogic* ingame = new IngameLogic(this->startCities[i]->player_ID, players[i], this->startCities[i]);
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
					erfg.push_back(static_cast<char>(this->neutralCities[i]->position->x));
					erfg.push_back(static_cast<char>(this->neutralCities[i]->position->y));
					erfg.push_back(this->neutralCities[i]->level);
				}
				for(unsigned int i = 0; i < this->startCities.size(); i++)
				{
					erfg.push_back(static_cast<char>(this->startCities[i]->position->x));
					erfg.push_back(static_cast<char>(this->startCities[i]->position->y));
					erfg.push_back(this->startCities[i]->level);
				}

				server->write(s, 0x0403, erfg);
			}break;
		case 0x0404:
			{
				int index;

				for(unsigned int i = 0; i < this->playersIngame.size(); i++)
				{
					if(this->playersIngame[i]->owner->s == s)
						index = i;
				}

				int length = this->playersIngame[index]->cities.size();

				erfg.push_back(length);

				for(unsigned int i = 0; i < this->playersIngame[index]->cities.size(); i++)
				{
					erfg.push_back(static_cast<char>(this->playersIngame[index]->cities[i]->position->x));
					erfg.push_back(static_cast<char>(this->playersIngame[index]->cities[i]->position->y));
					erfg.push_back(this->playersIngame[index]->cities[i]->level);
				}

				erfg.push_back(static_cast<char>(this->playersIngame[index]->cities[0]->player_ID));
		

				server->write(s, 0x0405, erfg);
			}break;
		case 0x0408:
			{	
				// sende alle einheitengruppen
				//umschreiben TODO
				for (unsigned int i = 0; i < this->playersIngame.size(); i++)
				{
					for (unsigned int j = 0; j < this->playersIngame[i]->unitGroups.size(); j++)
					{
							//send pos
								std::vector<char> tmp;
								tmp = code((int)this->playersIngame[i]->unitGroups[j]->pos.x);
								for (unsigned int l = 0; l < tmp.size(); l++)
									erfg.push_back(tmp[l]);
						
								tmp = code((int)this->playersIngame[i]->unitGroups[j]->pos.y);
								for (unsigned int l = 0; l < tmp.size(); l++)
									erfg.push_back(tmp[l]);

								// send strategy

								tmp = code((short)this->playersIngame[i]->unitGroups[j]->strategy);
								erfg.push_back(tmp[0]);
								erfg.push_back(tmp[1]);

								//send shorts living, type abwechselnd (16)
								unsigned int k;
								for (k = 0; k < this->playersIngame[i]->unitGroups[j]->units.size();k++)
								{
									tmp = code(this->playersIngame[i]->unitGroups[j]->units[k]->living);
									erfg.push_back(tmp[0]);
									erfg.push_back(tmp[1]);

									tmp = code((short)this->playersIngame[i]->unitGroups[j]->units[k]->type);
									erfg.push_back(tmp[0]);
									erfg.push_back(tmp[1]);
								}
								while (k < 16)
								{
									tmp = code((short) 0);
									erfg.push_back(tmp[0]);
									erfg.push_back(tmp[1]);

									tmp = code((short) 0);
									erfg.push_back(tmp[0]);
									erfg.push_back(tmp[1]);

									k++;
								}

					}
				}
					
				server->write(s, 0x0409, erfg);
			}break;
			case 0x0410:	//sende eigene Einheiten // umschreiben TODO
			{
				for (unsigned int i = 0; i < this->playersIngame.size(); i++)
				{
					if (this->playersIngame[i]->owner->s == s)
					{
						for (unsigned int j = 0; j < this->playersIngame[i]->unitGroups.size(); j++)
						{
								//send pos
								std::vector<char> tmp;
								tmp = code((int)this->playersIngame[i]->unitGroups[j]->pos.x);
								for (unsigned int l = 0; l < tmp.size(); l++)
									erfg.push_back(tmp[l]);
						
								tmp = code((int)this->playersIngame[i]->unitGroups[j]->pos.y);
								for (unsigned int l = 0; l < tmp.size(); l++)
									erfg.push_back(tmp[l]);

								// send strategy

								tmp = code((short)this->playersIngame[i]->unitGroups[j]->strategy);
								erfg.push_back(tmp[0]);
								erfg.push_back(tmp[1]);

								//send shorts living, type abwechselnd (16)
								unsigned int k;
								for (k = 0; k < this->playersIngame[i]->unitGroups[j]->units.size();k++)
								{
									tmp = code(this->playersIngame[i]->unitGroups[j]->units[k]->living);
									erfg.push_back(tmp[0]);
									erfg.push_back(tmp[1]);

									tmp = code((short)this->playersIngame[i]->unitGroups[j]->units[k]->type);
									erfg.push_back(tmp[0]);
									erfg.push_back(tmp[1]);
								}
								while (k < 16)
								{
									tmp = code((short) 0);
									erfg.push_back(tmp[0]);
									erfg.push_back(tmp[1]);

									tmp = code((short) 0);
									erfg.push_back(tmp[0]);
									erfg.push_back(tmp[1]);

									k++;
								}
						}
					}
				}
				server->write(s, 0x0411, erfg);
			}break;
			case 0x0412:
				{
					
				}break;
	}

}
	
void GameLogic::processNetworkError(SOCKET s,int errCode,std::string errMessage)
{

}