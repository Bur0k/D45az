#include "LogicData.h"

LogicData::LogicData()
{
	c = Client::get();
	c->addToNewMessageCallback(this);

	vector<char> erfg;
	c->write(0x0400, erfg);		//Spielernamen anfordern
}

LogicData::~LogicData()
{
	c->deleteFromNewMessageCallback(this);
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
	}
}

void LogicData::processNetworkError(int id, std::string msg)
{

}