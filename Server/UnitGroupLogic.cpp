#include "UnitGroupLogic.h"

UnitGroupLogic::UnitGroupLogic(short units, short type)
{
	for(unsigned int i = 0; i < units; i++)
	{
		UnitLogic* unit = new UnitLogic(type);

		this->units.push_back(unit);
	}
}

UnitGroupLogic::~UnitGroupLogic()
{

}

void UnitGroupLogic::processNewMessage(SOCKET s,short id,std::vector<char> data)
{
	switch(id)
	{

	}
}

void UnitGroupLogic::processNetworkError(SOCKET s,int errCode,std::string errMessage)
{
	switch(errCode)
	{

	}
}
