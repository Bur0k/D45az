#include "City.h"

City::City()
{
}

City::~City()
{
}

void City::processNewMessage(short id,vector<char> data)
{
	switch(id)
	{
	case 0x0:
		{

		}break;
	}
}

void City::processNetworkError(int id, std::string msg)
{

}