#include "UnitLogic.h"


UnitLogic::UnitLogic(UnitTypes type)
{
	this->living = maxlivingsoldiers;

	this->type = type;

	switch(type)
	{
		case UnitTypes::LIGHT:	
		{
			this->attackpower = light;
			this->range = 2;
			break;
		}
		case UnitTypes::HEAVY:	
		{
			this->attackpower = heavy;
			this->range = 3;
			break;
		}
		case UnitTypes::LONGRANGE:	
		{
			this->attackpower = longrange;
			this->range = 1;
			break;
		}
		case UnitTypes::ARTILLERY:
		{
			this->attackpower = artillery;
			this->range = 1;
			break;
		}
	}
}

UnitLogic::~UnitLogic()
{
}


