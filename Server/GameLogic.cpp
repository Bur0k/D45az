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
				CityLogic* c = new CityLogic(id, j, i);
				c->player_ID = 5;
				this->startCities.push_back(c);
				id++;
			}
			else if( v->layer[i][j] == NEUTRALCITY)
			{
				CityLogic* c = new CityLogic(id, j, i);
				c->player_ID = 5;
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
	
	for(unsigned int i = 0; i < this->movingArmies.size(); i++)
	{
		for(unsigned int j = 0; j < this->playersIngame[this->movingArmies[i]->playerID]->unitGroups.size(); j++)
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
		for(unsigned int i = 0; i < this->movingArmies.size(); i++)
		{
			armies[i]->pos = this->movingArmies[i]->move[0];
			this->movingArmies[i]->move.erase(this->movingArmies[i]->move.begin());
			
			this->isCollision(armies[i]->pos, armies);
		}

		for(unsigned int i = 0; i < this->movingArmies.size(); i++)
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
	UnitGroupLogic* currentArmy = armies[0];

	for(unsigned int i = 0; i < armies.size(); i++)
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
					erfg.push_back(static_cast<char>((this->neutralCities[i]->position->x)>>1));
					erfg.push_back(static_cast<char>((this->neutralCities[i]->position->y)>>1));
					erfg.push_back(this->neutralCities[i]->level);
					erfg.push_back(5);
				}
				for(unsigned int i = 0; i < this->startCities.size(); i++)
				{
					erfg.push_back(static_cast<char>((this->startCities[i]->position->x)>>1));
					erfg.push_back(static_cast<char>((this->startCities[i]->position->y)>>1));
					erfg.push_back(this->startCities[i]->level);
					erfg.push_back((char)this->startCities[i]->player_ID);
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
					erfg.push_back(static_cast<char>(this->playersIngame[index]->cities[i]->position->x)>>1);
					erfg.push_back(static_cast<char>(this->playersIngame[index]->cities[i]->position->y)>>1);
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
								tmp = code((int)this->playersIngame[i]->unitGroups[j]->pos->x>>1);
								for (unsigned int l = 0; l < tmp.size(); l++)
									erfg.push_back(tmp[l]);
						
								tmp = code((int)this->playersIngame[i]->unitGroups[j]->pos->y>>1);
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
								tmp = code((int)this->playersIngame[i]->unitGroups[j]->pos->x>>1);
								for (unsigned int l = 0; l < tmp.size(); l++)
									erfg.push_back(tmp[l]);
						
								tmp = code((int)this->playersIngame[i]->unitGroups[j]->pos->y>>1);
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

					for(unsigned int i = 1; i < data.size(); i++)
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

UnitGroupLogic GameLogic::fight(UnitGroupLogic army1, UnitGroupLogic army2) // Karre liefert nur Gewinner zur�ck, anderer tot
{

	while(army1.unitGroups->size() != 0 && army2.unitGroups->size() != 0) // Armeen haben noch Kompanien?
	{
		if(army1.unitGroups->size() > army2.unitGroups->size()) // ist Armee 1 gr��er, dann alle Kompanien von 2 durchgehen
		{
			for(unsigned int a = 0; a < army2.unitGroups->size(); a ++)
			{
				while(army1.units.size() != 0 && army2.units.size() != 0) // Kompanie hat noch Einheiten?
				{
					if(army1.units.size() > army2.units.size()) // Kompanie 1 gr��er, alle Einheiten der Kompanie 2 k�mpfen lassen
						for(unsigned int k = 0; k < army2.units.size(); k++)
						{
							// Kampf Einheit gegen Einheit
							double atk1 = 0.0;
							double atk2 = 0.0;

							switch (army1.strategy) // Armeeaufstellung 1 anrechnen
							{
							case UnitStrategy::DEFENSIVE: atk1 += def; break;
							case UnitStrategy::OFFENSIVE: atk1 += off; break;
							case UnitStrategy::RUNNING:   atk1 += run; break;
							}
							switch (army2.strategy) // Armeeaufstellung 2 anrechnen
							{
							case UnitStrategy::DEFENSIVE: atk2 += def; break;
							case UnitStrategy::OFFENSIVE: atk2 += off; break;
							case UnitStrategy::RUNNING:   atk2 += run; break;
							}
							
							atk1 += army1.units[k]->attackpower;
							atk2 += army2.units[k]->attackpower;

							atk1 += (rand()%100)/100.0;
							atk2 += (rand()%100)/100.0;

							if(atk1 > atk2)
								army1.units.erase(army1.units.begin()+k);
							else
								army2.units.erase(army2.units.begin()+k);
						}
					else 
					for(unsigned int k = 0; k < army1.units.size(); k++)
						{
							// Kampf Einheit gegen Einheit
							double atk1 = 0.0;
							double atk2 = 0.0;

							switch (army1.strategy) // Armeeaufstellung 1 anrechnen
							{
							case UnitStrategy::DEFENSIVE: atk1 += def; break;
							case UnitStrategy::OFFENSIVE: atk1 += off; break;
							case UnitStrategy::RUNNING:   atk1 += run; break;
							}
							switch (army2.strategy) // Armeeaufstellung 2 anrechnen
							{
							case UnitStrategy::DEFENSIVE: atk2 += def; break;
							case UnitStrategy::OFFENSIVE: atk2 += off; break;
							case UnitStrategy::RUNNING:   atk2 += run; break;
							}
							
							atk1 += army1.units[k]->attackpower;
							atk2 += army2.units[k]->attackpower;

							atk1 += (rand()%100)/100.0;
							atk2 += (rand()%100)/100.0;

							if(atk1 > atk2) // Einheit 1 oder Einheit 2 ist besiegt
								army1.units.erase(army1.units.begin()+k);
							else
								army2.units.erase(army2.units.begin()+k);
						}
				}
				
			// kein Plan ob richtige Stelle
				if(army1.unitGroups[a].size() == 0) // entweder Kompanie 1 oder Kompanie 2 ist besiegt
					army1.unitGroups->erase(army1.unitGroups->begin()+a);
				else
					army2.unitGroups->erase(army2.unitGroups->begin()+a);

			}
		}
		else
		{
			for(unsigned int a = 0; a < army1.unitGroups->size(); a ++)
			{
				while(army1.units.size() != 0 && army2.units.size() != 0) // Kompanie hat noch Einheiten?
				{
					if(army1.units.size() > army2.units.size()) // Kompanie 1 gr��er, alle Einheiten der Kompanie 2 k�mpfen lassen
					{
						for(unsigned int k = 0; k < army2.units.size(); k++)
						{
							// Kampf Einheit gegen Einheit
							double atk1 = 0.0;
							double atk2 = 0.0;

							switch (army1.strategy) // Armeeaufstellung 1 anrechnen
							{
							case UnitStrategy::DEFENSIVE: atk1 += def; break;
							case UnitStrategy::OFFENSIVE: atk1 += off; break;
							case UnitStrategy::RUNNING:   atk1 += run; break;
							}
							switch (army2.strategy) // Armeeaufstellung 2 anrechnen
							{
							case UnitStrategy::DEFENSIVE: atk2 += def; break;
							case UnitStrategy::OFFENSIVE: atk2 += off; break;
							case UnitStrategy::RUNNING:   atk2 += run; break;
							}

							atk1 += army1.units[k]->attackpower;
							atk2 += army2.units[k]->attackpower;

							atk1 += (rand()%100)/100.0;
							atk2 += (rand()%100)/100.0;

							if(atk1 > atk2)
								army1.units.erase(army1.units.begin()+k);
							else
								army2.units.erase(army2.units.begin()+k);
						}
					}
					else 
					{
					for(unsigned int k = 0; k < army1.units.size(); k++)
						{
							// Kampf Einheit gegen Einheit
							double atk1 = 0.0;
							double atk2 = 0.0;

							switch (army1.strategy) // Armeeaufstellung 1 anrechnen
							{
							case UnitStrategy::DEFENSIVE: atk1 += def; break;
							case UnitStrategy::OFFENSIVE: atk1 += off; break;
							case UnitStrategy::RUNNING:   atk1 += run; break;
							}
							switch (army2.strategy) // Armeeaufstellung 2 anrechnen
							{
							case UnitStrategy::DEFENSIVE: atk2 += def; break;
							case UnitStrategy::OFFENSIVE: atk2 += off; break;
							case UnitStrategy::RUNNING:   atk2 += run; break;
							}
							
							atk1 += army1.units[k]->attackpower;
							atk2 += army2.units[k]->attackpower;

							atk1 += (rand()%100)/100.0; 
							atk2 += (rand()%100)/100.0;

							if(atk1 > atk2)
								army1.units.erase(army1.units.begin()+k);
							else
								army2.units.erase(army2.units.begin()+k);
						}
					}
				}
							
				// kein Plan ob richtige Stelle
				if(army1.unitGroups[a].size() == 0) // entweder Kompanie 1 oder Kompanie 2 ist besiegt
					army1.unitGroups->erase(army1.unitGroups->begin()+a);
				else
					army2.unitGroups->erase(army2.unitGroups->begin()+a);
			}		
		}
	}
	if(army1.unitGroups->size() == 0)
		return army2;
	else
		return army1;
}