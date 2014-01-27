#include "LogicData.h"

LogicData::LogicData()
{
	c = Client::get();
	c->addToNewMessageCallback(this);

	this->updateGameData();
}

LogicData::~LogicData()
{
	c->deleteFromNewMessageCallback(this);
}

void LogicData::updateGameData()
{
	this->requestAllCities();
	this->requestAllUnits();
	this->requestBarricades();
	this->requestOwnedCities();
	this->requestOwnedUnits();
	this->requestPlayers();
}

void LogicData::requestPlayers()
{
	vector<char> erfg;
	c->write(0x0400, erfg);
}

void LogicData::requestAllCities()
{
	vector<char> erfg;
	c->write(0x0402, erfg);
}

void LogicData::requestOwnedCities()
{
	vector<char> erfg;
	c->write(0x0404, erfg);
}

void LogicData::requestBarricades()
{
	vector<char> erfg;
	c->write(0x0406, erfg);
}

void LogicData::requestAllUnits()
{
	vector<char> erfg;
	c->write(0x0400, erfg);
}

void LogicData::requestOwnedUnits()
{
	vector<char> erfg;
	c->write(0x0400, erfg);
}

void LogicData::processNewMessage(short id,vector<char> data)
{
	vector<char> erfg;

	switch(id)
	{
	case 0x0401:
		{
			string name;

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
			sf::Vector2i pos;
			int level;

			for(int i = 0; i < length; i++)
			{
				pos.x = data[1];
				pos.y = data[2];
				level = data[3];

				City* c = new City(pos, level);

				this->allCities.push_back(c);

				data.erase(data.begin() + 1, data.begin() + 3);
			}
		}break;
	case 0x0405:
		{
			int length = data[0];
			sf::Vector2i pos;
			int level;

			for(int i = 0; i < length; i++)
			{
				pos.x = data[1];
				pos.y = data[2];
				level = data[3];

				City* c = new City(pos, level);

				this->ownedCities.push_back(c);

				data.erase(data.begin() + 1, data.begin() + 3);
			}
		}break;
	case 0x0407:
		{
			sf::Vector2i pos;

			for(int i = 0; i < data.size(); i = i + 2)
			{
				pos.x = data[i];
				pos.y = data[i + 1];

				this->barricades.push_back(pos);
			}
		}break;
}
}

void LogicData::processNetworkError(int id, std::string msg)
{

}