#ifndef PARMY_H
#define PARMY_H

#include <math.h>
#include "UnitGroupLogic.h"

struct pArmy
{
	vector<POINT*> move;
	int playerID;
	UnitGroupLogic* army;

	pArmy(int playerID, vector<POINT*> move);
};

#endif
