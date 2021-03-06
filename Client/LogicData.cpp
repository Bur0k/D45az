#include "LogicData.h"

LogicData::LogicData()
{
	c = Client::get();
	c->addToNewMessageCallback(this);

	this->serverReady  = false;
	this->updateGameData();
}

LogicData::~LogicData()
{
	c->deleteFromNewMessageCallback(this);
}

void LogicData::updateGameData()
{
	this->requestPlayers();
	this->requestOwnedCities();
	this->requestOwnedUnits();
	this->requestAllCities();
	this->requestAllUnits();	
}

void LogicData::requestPlayers()
{
	vector<unsigned char> erfg;
	erfg.push_back(0);
	c->write(0x0400, erfg);
}

void LogicData::requestAllCities()
{
	vector<unsigned char> erfg;
	c->write(0x0402, erfg);
}

void LogicData::requestOwnedCities()
{
	vector<unsigned char> erfg;
	c->write(0x0404, erfg);
}

void LogicData::requestAllUnits()
{
	vector<unsigned char> erfg;
	c->write(0x0408, erfg);
}

void LogicData::requestOwnedUnits()
{
	vector<unsigned char> erfg;
	c->write(0x0410, erfg);
}

void LogicData::requestGold()
{
	vector<unsigned char> erfg;
	erfg.push_back((unsigned char)this->ownedCities[0]->player_ID);
	c->write(0x0418, erfg);
}

void LogicData::processNewMessage(short id,vector<unsigned char> data)
{
	vector<unsigned char> erfg;

	switch(id)
	{
	case 0x0401:
		{
			string name;

			this->playersIngame.clear();

			for(unsigned int i = 0; i < data.size(); i++)
			{
				if(data[i] != '/')
					name += data[i];
				else
				{
					this->playersIngame.push_back(name);
					name.clear();
				}
			}
		}break;
	case 0x0403:
		{
			int length = data[0];
			short playerID;
			sf::Vector2i pos;
			int level;

			this->allCities.clear();

			for(int i = 0; i < length; i++)
			{
				pos.x = data[1];
				pos.y = data[2];
				level = data[3];
				playerID = data[4];

				City* c = new City(pos, level, playerID);

				this->allCities.push_back(c);

				data.erase(data.begin() + 1, data.begin() + 5);	//achtung
			}
		}break;
	case 0x0405:
		{
			short player_ID;
			int length = data[0];
			sf::Vector2i pos;
			int level;

			this->ownedCities.clear();

			for(int i = 0; i < length; i++)
			{
				pos.x = data[1];
				pos.y = data[2];
				level = data[3];
				player_ID = data[4];

				City* c = new City(pos, level, player_ID);

				this->ownedCities.push_back(c);

				data.erase(data.begin() + 1, data.begin() + 5);
			}
		}break;
	case 0x0409:
		{
			for (unsigned int i = 0; i < data.size(); i+=78)
			{
				for(auto it : allUnits)
					delete it;
				allUnits.clear();
				
				UnitStrategy strategy;
				UnitTypes types[16];
				short livingsoldiers[16];
				POINT pos;

				i+=4;//kurz was umgehen

				//pos auslesen
				pos.x = decodeInt(data, i);
				pos.y = decodeInt(data, i + 4);
				// strategy(short) auslesen
				strategy = (UnitStrategy) decodeShort(data, i + 8);
				// 32 shorts abwechselnd living und type
				for (int j = 0; j < 16; j++)
				{
					//vertauscht
					types[j] = (UnitTypes)decodeShort(data, i + 10 + 4 * j + 2);
					livingsoldiers[j] =  decodeShort(data, i + 10 + 4*j);				
				}
				i-=4;//kurz was umgehen

				UnitGroup* ugroup = new UnitGroup(pos, types, livingsoldiers, strategy, decodeInt(data,i));
				allUnits.push_back(ugroup);
			}	
		}break;
	case 0x0411:
		{
			bool enable = false;	// Sperre für setValue der Statusbar, da sie bei der ersten Datenübertragung noch nicht vorhanden ist
			if(this->ownedUnits.size() != 0)
				enable = true;

			ownedUnits.clear();

			for (unsigned int i = 0; i < data.size(); i+=74)
			{
				
				
				UnitStrategy strategy;
				UnitTypes types[16];
				short livingsoldiers[16];
				POINT pos;
				//pos auslesen
				pos.x = decodeInt(data, i);
				pos.y = decodeInt(data, i + 4);
				// strategy(short) auslesen
				strategy = (UnitStrategy) decodeShort(data, i + 8);
				// 32 shorts abwechselnd living und type
				for (int j = 0; j < 16; j++)
				{

					types[j] = (UnitTypes)decodeShort(data, i + 10 + 4 * j + 2);
					livingsoldiers[j] =  decodeShort(data, i + 10 + 4*j);

				}

				UnitGroup* ugroup = new UnitGroup(pos, types, livingsoldiers, strategy, ownedCities[0]->player_ID);
				ownedUnits.push_back(ugroup);
				
				/*if(enable)
				{*/
					erfg.clear();	
					c->write(0x0601, erfg);	// Message an den Server -> Alle neuen Daten eingelesen
				//}
			}
		}break;
	case 0x0413:
		{
			stringstream str;
			string st;
			int g;
			for(int i = 0; i < data.size(); i++)
			{
				st += data[i];
			}
			str << st;
			str >> g;

			this->gold = g;
		}break;
	case 0x0415:
		{		
			this->serverReady = true;
		}break;
	case 0x0417:
		{
			// data enthält alle Moves die durchgeführt werden

			// z.B data[0] -> playerID
			// data[1] -> x Koordinate
			// data[2] -> y Koordinate
		}break;
}
}

void LogicData::processNetworkError(int id, std::string msg)
{

}