#include "LogicData.h"

LogicData::LogicData()
{
	c = Client::get();
	c->addToNewMessageCallback(this);
}

LogicData::~LogicData()
{
	c->deleteFromNewMessageCallback(this);
}

void LogicData::processNewMessage(short id,vector<char> data)
{
	switch(id)
	{
	case 0x0400:
		{

		}break;
	}
}

void LogicData::processNetworkError(int id, std::string msg)
{

}