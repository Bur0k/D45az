#include "GameLogic.h"

GameLogic::GameLogic(vector<PlayerData> players, Map* map)
{
	this->server = Server::get();

	server->addToNewMessageCallback(this);
	server->addToErrorCallback(this);

	this->playerCommits = 0;
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
			int x1 = this->playersIngame[this->movingArmies[i]->playerID]->unitGroups[j]->pos->x;
			int y1 = this->playersIngame[this->movingArmies[i]->playerID]->unitGroups[j]->pos->y;
			int x2 = this->movingArmies[i]->move[0]->x;
			int y2 = this->movingArmies[i]->move[0]->y;

			if(x1 == x2 && y1 == y2)
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
					// FIGHT
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
		case 0x0400: // Client fordert die Spielernamen aller Teilnehmer an
			{
				for(int i = 0; i < (signed) this->playersIngame.size(); i++)
				{
					string name = this->playersIngame[i]->owner.Name;
					vector<char> tmp = code(name);

					erfg.insert(erfg.end(), tmp.begin(), tmp.end());
					erfg.push_back('/');
				}

				server->write(s, 0x0401, erfg);
			}break;
		case 0x0402: // Client fordert Daten aller Städte auf der Karte an
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
		case 0x0404: // Client fordert Daten der eigenen Städte an
			{
				int index;

				for(unsigned int i = 0; i < this->playersIngame.size(); i++)
				{
					if(this->playersIngame[i]->owner.s == s)
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

				// Gold übertragen

				erfg.clear();

				erfg = this->divideForMessage(this->playersIngame[index]->gold);

				server->write(s, 0x0413, erfg);
			}break;
		case 0x0408:
			{	
				// sende alle einheitengruppen
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
			case 0x0410:	//sende eigene Einheiten 
			{
				for (unsigned int i = 0; i < this->playersIngame.size(); i++)
				{
					if (this->playersIngame[i]->owner.s == s)
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
			case 0x0412: // Auswerten der übertragenen Einheitenbewegungen nach dem Commit
				{
					vector<POINT*> vp;
					POINT* p = new POINT();
					vector<char> erfg;

					int player_ID = data[0];

					for(unsigned int i = 1; i < data.size(); i++)
					{
						if(data[i] == '/')
						{
							if(vp.size() > 1)
							{
								pArmy* movingArmy = new pArmy(player_ID, vp);
								this->movingArmies.push_back(movingArmy);
							}
						}
						else
						{
							if( i % 2 != 0)
							{
								p->x = data[i] * 2;
							}
							else
							{
								p->y = data[i] * 2;
								vp.push_back(p);
								p = new POINT();
							}
						}
						
					}

					this->playerCommits++;

					if(this->playerCommits == this->playersIngame.size())
					{
						// Erstellen eines Vektors mit allen Bewegungen zur Client Visualisierung

						for(int i = 0; i < this->movingArmies.size(); i++)
						{
							erfg.push_back(this->movingArmies[i]->playerID);

							for(int j = 0; j < this->movingArmies[i]->move.size(); j++)
							{
								erfg.push_back(this->movingArmies[i]->move[j]->x);
								erfg.push_back(this->movingArmies[i]->move[j]->y);
							}

							erfg.push_back('/');
						}

						this->computeTurns();

						for(unsigned int i = 0; i < this->playersIngame.size(); i++)
						{
							server->write(this->playersIngame[i]->owner.s, 0x0417, erfg);

							for(unsigned  j = 0; j < this->playersIngame[i]->cities.size(); j++)
							{
								this->playersIngame[i]->gold += this->playersIngame[i]->cities[j]->generatedIncome;
							}
						}


						for(unsigned int i = 0; i < this->playersIngame.size(); i++)
						{							
							server->write(this->playersIngame[i]->owner.s, 0x0600, erfg);
						}
			
						this->playerCommits = 0;
					}
					else
					{
						while(this->playerCommits < this->playersIngame.size()){}

						this->computeTurns();
					}
				}break;
				case 0x0414: // Auswertung Stadtaktionen nach Commit (Einheiten ausbilden, Stadt aufwerten)
				{
						// Message: (Position x city, Position y city, Anzahl Truppen Group, Unittype, bool cityUpgrade, ...)

					POINT p;

					for(unsigned int i = 0; i < (data.size()>>1); i++)
					{
						short playerID = data[0];
						p.x = data[1];
						p.y = data[2];
						int armyCount = data[3];
						short type = data[4];
						UnitTypes atype;

						switch(type)
						{
						case 0:
							{
								atype = UnitTypes::LIGHT;
							}break;
						case 1:
							{
								atype = UnitTypes::HEAVY;
							}break;
						case 2:
							{
								atype = UnitTypes::LONGRANGE;
							}break;
						case 3:
							{
								atype = UnitTypes::ARTILLERY;
							}break;
						}

						bool isCityUpgraded = false;
						if(data[5] == 1)
							isCityUpgraded = true;

						for(unsigned int i = 0; i < this->playersIngame[playerID]->cities.size(); i++)
						{
							if(this->playersIngame[playerID]->cities[i]->position == &p)
							{
								if(this->playersIngame[playerID]->cities[i]->upgradeCity())
									this->playersIngame[playerID]->gold -= 500;
							}
						}

						p.y += 2;

						for(unsigned int i = 0; i < this->playersIngame.size(); i++)
						{
							for(int j = 0; this->playersIngame[i]->unitGroups.size(); j++)
							{
								if(this->playersIngame[i]->unitGroups[j]->pos == &p)
									p.y += 2;
							}
						}

						UnitGroupLogic newGroup = UnitGroupLogic(armyCount, atype, p, &this->playersIngame[playerID]->unitGroups);

						data.erase(data.begin() + 6);
					}
				}break;
				case 0x0416:
					{
						for(unsigned int i = 0; i < this->playersIngame.size(); i++)
						{
							for(unsigned int k = 0; k < this->playersIngame[i]->unitGroups.size(); k++)
							{
								if(this->playersIngame[i]->unitGroups[k]->pos->x == data[0])
									if(this->playersIngame[i]->unitGroups[k]->pos->y == data[1])
									{
										switch(data[2])
						{
											case 0: 
												{this->playersIngame[i]->unitGroups[k]->strategy = UnitStrategy::DEFENSIVE;}break;
											case 1: 
												{this->playersIngame[i]->unitGroups[k]->strategy = UnitStrategy::OFFENSIVE;}break;
											case 2: 
												{this->playersIngame[i]->unitGroups[k]->strategy = UnitStrategy::RUNNING;}break;
										}

											data.erase(data.begin(), data.begin() + 2);
									}
							}
						}
					}break;
				case 0x0601:
					{
						server->write(s, 0x0602, erfg); // Freigabe an Client für Statusbarupdate
						server->write(s, 0x0415, erfg); // Server ist fertig mit allen Berechnungen
					}break;
			case 0x1000://Chat empfangen
				{
					for(auto it : playersIngame)
					{
						if(s == it->owner.s)//Ist der Spieler in DIESER Lobby?
						{
							string chatToSend = it->owner.Name + ": "+decodeString(data,0,data.size());
							std::vector<char> toSend = code(chatToSend);

							for(auto it2 : playersIngame)
								server->write(it2->owner.s,0x1001,toSend);
							break;
						}
					}
				}break;
	}

}
	
vector<char> GameLogic::divideForMessage(int number)
{
	vector<char> erfg;

	std::stringstream sstr;
	sstr << number;

	for(int i = 0; i < sstr.str().size(); i++)
		erfg.push_back(sstr.str()[i]);

	return erfg;
}
	
void GameLogic::processNetworkError(SOCKET s,int errCode,std::string errMessage)
{

}

UnitGroupLogic GameLogic::fight(UnitGroupLogic army1, UnitGroupLogic army2) // Karre liefert nur Gewinner zurück, anderer tot
{
	while(army1.units.size() != 0 && army2.units.size() != 0) // bis eine Armee keine Kompanien mehr hat
	{
                if(army1.units.size() < army2.units.size())
		{
                    int Kompanies = army1.units.size();
                    for (int k = 0; k < Kompanies; k++) // alle Kompanien kämpfen 
			{
                        while(army1.units[k]->living != 0 && army2.units[k]->living != 0) // bis eine Kompanie keine Einheiten mehr hat
				{
                            if(army1.units[k]->living < army2.units[k]->living)
						{
                                int Einheiten = army1.units[k]->living;
                                for(int u = 0; u < Einheiten; u++) // alle Einheiten der Kompanie kämpfen lassen
                                {
							double atk1 = 0.0;
							double atk2 = 0.0;

                                    switch(army1.strategy) // ArmeeStrategie
							{
							case UnitStrategy::OFFENSIVE: atk1 += off; break;
									case UnitStrategy::DEFENSIVE: atk1 += def; break;
									case UnitStrategy::RUNNING:	atk1 += run; break;
							}
                                    switch(army2.strategy)
							{
							case UnitStrategy::OFFENSIVE: atk2 += off; break;
                                        case UnitStrategy::DEFENSIVE: atk2 += def; break;
                                        case UnitStrategy::RUNNING: atk2 += run; break;
							}
							
									switch(army1.units[k]->type) // KompanieTyp
                                    {
									case UnitTypes::LIGHT: atk1 += light; break;
                                    case UnitTypes::HEAVY: atk1 += heavy; break;
                                    case UnitTypes::LONGRANGE: atk1 += longrange; break;
                                    case UnitTypes::ARTILLERY: atk1 += artillery; break;
                                    }
                                    switch(army2.units[k]->type)
                                    {
                                    case UnitTypes::LIGHT: atk2 += light; break;
                                    case UnitTypes::HEAVY: atk2 += heavy; break;
                                    case UnitTypes::LONGRANGE: atk2 += longrange; break;
                                    case UnitTypes::ARTILLERY: atk2 += artillery; break;
                                    }


                                    double bonus = 0.0;
                                    bonus = (rand() % 100) / 100.0;  // 1. Bonus zwischen 0,00 und 1,00
                                    atk1 += bonus;
                                    bonus = (rand() % 100) / 100.0;
                                    atk2 += bonus;

                                    if(atk1 < atk2)
                                        army1.units[k]->living --;
							else
                                        army2.units[k]->living --;
						}
						}
					else 
						{
                                int Einheiten = army2.units[k]->living;
                                for(int u = 0; u < Einheiten; u++) // alle Einheiten der Kompanie kämpfen lassen
                                {
							double atk1 = 0.0;
							double atk2 = 0.0;

                                    switch(army1.strategy) // ArmeeStrategie
							{
							case UnitStrategy::OFFENSIVE: atk1 += off; break;
									case UnitStrategy::DEFENSIVE: atk1 += def; break;
									case UnitStrategy::RUNNING: atk1 += run; break;
							}
                                    switch(army2.strategy)
							{
							case UnitStrategy::OFFENSIVE: atk2 += off; break;
                                    case UnitStrategy::DEFENSIVE: atk2 += def; break;
                                    case UnitStrategy::RUNNING: atk2 += run; break;
							}
							
                                    switch(army1.units[k]->type) // KompanieTyp
                                    {
									case UnitTypes::LIGHT: atk1 += light; break;
									case UnitTypes::HEAVY: atk1 += heavy; break;
									case UnitTypes::LONGRANGE: atk1 += longrange; break;
									case UnitTypes::ARTILLERY: atk1 += artillery; break;
                                    }
                                    switch(army2.units[k]->type)
                                    {
									case UnitTypes::LIGHT: atk2 += light; break;
									case UnitTypes::HEAVY: atk2 += heavy; break;
									case UnitTypes::LONGRANGE: atk2 += longrange; break;
									case UnitTypes::ARTILLERY: atk2 += artillery; break;
                                    }

                                    double bonus = 0.0;
                                    bonus = (rand() % 100) / 100.0;  // 1. Bonus zwischen 0,00 und 1,00
                                    atk1 += bonus;
                                    bonus = (rand() % 100) / 100.0;
                                    atk2 += bonus;

                                    if(atk1 < atk2)
                                        army1.units[k]->living --;
							else
                                        army2.units[k]->living --;
						}
				}
                        }
				
                    if(army1.units[k]->living == 0) // Wenn Kompanie auf 0 Einheiten reduziert wird, löschen
						army1.units.erase(army1.units.begin()+k);
                    else if (army2.units[k]->living == 0)
                        army2.units.erase(army2.units.begin()+k);

                    if (army1.units.size() < army2.units.size()) // Max neusetzen, damit nicht verstorbene Kompanien bearbeitet werden
                        Kompanies = army1.units.size();
				else
                        Kompanies = army2.units.size();
			}
		}
		else
		{
                    int Kompanies = army2.units.size();
                    for(int k = 0; k < Kompanies; k++) // alle Kompanien kämpfen 
			{
                        while(army1.units[k]->living != 0 && army2.units[k]->living != 0) // bis eine Kompanie keine Einheiten mehr hat
				{
                            if(army1.units[k]->living < army2.units[k]->living)
					{
                                int Einheiten = army1.units[k]->living;
                                for(int u = 0; u < Einheiten; u++) // alle Einheiten der Kompanie kämpfen lassen
						{
							double atk1 = 0.0;
							double atk2 = 0.0;

                                    switch(army1.strategy) // ArmeeStrategie
							{
									case UnitStrategy::OFFENSIVE: atk1 += off; break;
							case UnitStrategy::DEFENSIVE: atk1 += def; break;
									case UnitStrategy::RUNNING: atk1 += run; break;
							}
                                    switch(army2.strategy)
							{
									case UnitStrategy::OFFENSIVE: atk2 += off; break;
							case UnitStrategy::DEFENSIVE: atk2 += def; break;
									case UnitStrategy::RUNNING: atk2 += run; break;
							}

                                    switch(army1.units[k]->type) // KompanieTyp
                                    {
									case UnitTypes::LIGHT: atk1 += light; break;
									case UnitTypes::HEAVY: atk1 += heavy; break;
									case UnitTypes::LONGRANGE: atk1 += longrange; break;
									case UnitTypes::ARTILLERY: atk1 += artillery; break;
                                    }
                                    switch(army2.units[k]->type)
                                    {
									case UnitTypes::LIGHT: atk2 += light; break;
									case UnitTypes::HEAVY: atk2 += heavy; break;
									case UnitTypes::LONGRANGE: atk2 += longrange; break;
									case UnitTypes::ARTILLERY: atk2 += artillery; break;
                                    }

                                    double bonus = 0.0;
                                    bonus = (rand() % 100) / 100.0;  // 1. Bonus zwischen 0,00 und 1,00
                                    atk1 += bonus;
                                    bonus = (rand() % 100) / 100.0;
                                    atk2 += bonus;

                                    if(atk1 < atk2)
                                        army1.units[k]->living --;
							else
                                        army2.units[k]->living --;
						}
					}
					else 
					{
                                int Einheiten = army2.units[k]->living;
                                for(int u = 0; u < Einheiten; u++) // alle Einheiten der Kompanie kämpfen lassen
						{
							double atk1 = 0.0;
							double atk2 = 0.0;

                                    switch(army1.strategy) // ArmeeStrategie
							{
									case UnitStrategy::OFFENSIVE: atk1 += off; break;
							case UnitStrategy::DEFENSIVE: atk1 += def; break;
									case UnitStrategy::RUNNING: atk1 += run; break;
							}
                                    switch(army2.strategy)
							{
									case UnitStrategy::OFFENSIVE: atk2 += off; break;
							case UnitStrategy::DEFENSIVE: atk2 += def; break;
									case UnitStrategy::RUNNING: atk2 += run; break;
							}
							
                                    switch(army1.units[k]->type) // KompanieTyp
                                    {
									case UnitTypes::LIGHT: atk1 += light; break;
									case UnitTypes::HEAVY: atk1 += heavy; break;
									case UnitTypes::LONGRANGE: atk1 += longrange; break;
									case UnitTypes::ARTILLERY: atk1 += artillery; break;
                                    }
                                    switch(army2.units[k]->type)
                                    {
									case UnitTypes::LIGHT: atk2 += light; break;
									case UnitTypes::HEAVY: atk2 += heavy; break;
									case UnitTypes::LONGRANGE: atk2 += longrange; break;
									case UnitTypes::ARTILLERY: atk2 += artillery; break;
                                    }

                                    double bonus = 0.0;
                                    bonus = (rand() % 100) / 100.0;  // 1. Bonus zwischen 0,00 und 1,00
                                    atk1 += bonus;
                                    bonus = (rand() % 100) / 100.0;
                                    atk2 += bonus;

                                    if(atk1 < atk2)
                                        army1.units[k]->living --; // STerben der Einheiten
							else
                                        army2.units[k]->living --;
						}
					}
				}
							
                        if (army2.units[k]->living == 0) // Wenn Kompanie auf 0 Einheiten reduziert wird, löschen
                            army2.units.erase(army2.units.begin()+k);
                        else if (army1.units[k]->living == 0)
                            army1.units.erase(army1.units.begin()+k);

                        if (army1.units.size() < army2.units.size()) // Max neusetzen, damit nicht verstorbene Kompanien bearbeitet werden
                            Kompanies = army1.units.size();
				else
                            Kompanies = army2.units.size();
			}		
		}
	}
	
	if(army1.units.size() == 0)
		return army2;
	else
		return army1;
}