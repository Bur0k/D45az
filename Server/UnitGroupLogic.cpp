#include "UnitGroupLogic.h"

UnitGroupLogic::UnitGroupLogic()
{

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
