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
	}
}

void LogicData::processNetworkError(int id, std::string msg)
{

}