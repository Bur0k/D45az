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
		for(unsigned int j = 0; j < v->layer[i].size(); j += 2)
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

void GameLogic::computeTurns()
{
	vector<UnitGroupLogic*> armies;
	
	for(int i = 0; i < this->movingArmies.size(); i++)
	{
		for(int j = 0; j < this->playersIngame[this->movingArmies[i]->playerID]->unitGroups.size(); j++)
		{
			if(this->playersIngame[this->movingArmies[i]->playerID]->unitGroups[j]->pos == this->movingArmies[i]->move[0])
			{
				armies.push_back(this->playersIngame[this->movingArmies[i]->playerID]->unitGroups[j]);
			}
		}

		this->movingArmies[i]->move.erase(this->movingArmies[i]->move.begin());
	}

	while(this->movingArmies.size() > 0)
	{
		for(int i = 0; i < this->movingArmies.size(); i++)
		{
			armies[i]->pos = this->movingArmies[i]->move[0];
			this->movingArmies[i]->move.erase(this->movingArmies[i]->move.begin());
			
			this->isCollision(armies[i]->pos, armies);
		}

		for(int i = 0; i < this->movingArmies.size(); i++)
		{
			if(this->movingArmies[i]->move.size() == 0)
			{
				this->movingArmies.erase(this->movingArmies.begin() + i);
				armies.erase(armies.begin() + i);
			}
		}
	}
}

void GameLogic::isCollision(POINT* pos, vector<UnitGroupLogic*> armies)
{
	UnitGroupLogic* currentArmy;

	for(int i = 0; i < armies.size(); i++)
	{
		if(armies[i]->pos == pos)
		{
			currentArmy = armies[i];
			armies.erase(armies.begin() + i);
		}
	}

	for(auto it=armies.begin();it!=armies.end();it++)
	{
		POINT p1 = (*(*it)->pos);
		for(auto it2=it+1;it2!=armies.end();it2++)
		{
			POINT p2 = (*(*it)->pos);
			POINT p3;
			p3.x=std::abs(p1.x-p2.x);
			p3.y=std::abs(p1.y-p2.y);
			const int RANGE = 2;
			if(p3.x <= RANGE && p3.y <= RANGE)
			{
				if(currentArmy->player_ID == (*it)->player_ID)
				{
					// Abfrage Einheitenmerge
				}
				else
				{
					// Kampf
				}
			}
		}
	}
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
								tmp = code((int)this->playersIngame[i]->unitGroups[j]->pos->x);
								for (unsigned int l = 0; l < tmp.size(); l++)
									erfg.push_back(tmp[l]);
						
								tmp = code((int)this->playersIngame[i]->unitGroups[j]->pos->y);
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
								tmp = code((int)this->playersIngame[i]->unitGroups[j]->pos->x);
								for (unsigned int l = 0; l < tmp.size(); l++)
									erfg.push_back(tmp[l]);
						
								tmp = code((int)this->playersIngame[i]->unitGroups[j]->pos->y);
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
					vector<POINT*> vp;
					POINT* p = new POINT();

					int player_ID = data[0];

					for(int i = 1; i < data.size(); i++)
					{
						if(data[i] == '/')
						{
							pArmy* movingArmy = new pArmy(player_ID, vp);
							this->movingArmies.push_back(movingArmy);
						}
						else
						{
							if( i % 2 != 0)
							{
								p->x = data[i];
							}
							else
							{
								p->y = data[i];
								vp.push_back(p);							
							}
						}
						
					}

					this->playerCommits++;

					if(this->playerCommits == this->playersIngame.size())
					{
						this->computeTurns();
						this->playerCommits = 0;
					}
				}break;

			case 0x1000://Chat empfangen
				{
					for(auto it : playersIngame)
					{
						if(s == it->owner->s)//Ist der Spieler in DIESER Lobby?
						{
							string chatToSend = it->owner->Name + ": "+decodeString(data,0,data.size());
							std::vector<char> toSend = code(chatToSend);

							for(auto it2 : playersIngame)
								server->write(it2->owner->s,0x1001,toSend);
							break;
						}
					}
				}break;
	}

}
	
void GameLogic::processNetworkError(SOCKET s,int errCode,std::string errMessage)
{

}