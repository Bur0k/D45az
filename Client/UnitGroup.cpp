#include "UnitGroup.h"

UnitGroup::UnitGroup()
{
}

UnitGroup::~UnitGroup()
{
}

void UnitGroup::processNewMessage(short id,vector<char> data)
{
	switch(id)
	{
	case 0x0:
		{

		}break;
	}
}

void UnitGroup::processNetworkError(int id, std::string msg)
{

}