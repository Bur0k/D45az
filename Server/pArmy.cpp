#include "pArmy.h"

pArmy::pArmy(int playerID, POINT* position, UnitGroupLogic* army)
{
	this->army = army;
	this->playerID = playerID;
	this->position = position;
}