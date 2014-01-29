#include "UnitGroupLogic.h"

UnitGroupLogic::UnitGroupLogic(short units, UnitTypes type, POINT pos,  vector<UnitGroupLogic*>* unitGroups)
{
	this->pos.x = pos.x;
	this->pos.y = pos.y;

	this->unitGroups = unitGroups;

	for(int i = 0; i < units; i++)
	{
		UnitLogic* unit = new UnitLogic(type);

		this->units.push_back(unit);
	}

	this->unitGroups->push_back(this);
}

UnitGroupLogic::~UnitGroupLogic()
{
	for (unsigned int i = 0; i < units.size(); i++)
		delete this->units[i];
}

void UnitGroupLogic::moveOneStep(POINT to)
{
	this->pos.x = to.x;
	this->pos.y = to.y;
}


void UnitGroupLogic::addUnit(short units, UnitTypes type)
{
	for (int i = 0; i < units; i++)
		UnitLogic* unit = new UnitLogic(type);
}


void UnitGroupLogic::removeUnit(short units, UnitTypes type)
{
	for (int i = 0; i < units; i++)
	{
		for (unsigned int j = 0; j < this->units.size(); j++)
		{
			if (this->units[j]->type == type)
			{
				delete this->units[j];
				this->units.erase(this->units.begin() + j);
				break;
			}
		}
	}
	if (this->units.size() == 0)
		delete this;
}

void UnitGroupLogic::move(POINT moves[], int arrlen)
{
	for (int i = 0; i < arrlen; i++)
		this->moveOneStep(moves[i]);
}

void UnitGroupLogic::splitandMove(short units[], UnitTypes types[], POINT moves[], int arrlen)
{
	UnitGroupLogic* splittedGroup = new UnitGroupLogic(units[0], types[0], this->pos, this->unitGroups);


	for (int i = 1; i < 4; i++)
		splittedGroup->addUnit(units[i], types[i]);

	for (int i = 0; i < 4; i++)
		this->removeUnit(units[i], types[i]);


	splittedGroup->move(moves, arrlen);

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
