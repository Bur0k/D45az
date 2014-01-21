#include "Ingame.h"

Ingame::Ingame()
{
}

Ingame::~Ingame()
{
}

void Ingame::processNewMessage(short id,vector<char> data)
{
	switch(id)
	{
	case 0x0:
		{

		}break;
	}
}

void Ingame::processNetworkError(int id, std::string msg)
{

}