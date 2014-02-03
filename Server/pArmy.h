#ifndef PARMY_H
#define PARMY_H

#include <math.h>
#include "UnitGroupLogic.h"

struct pArmy
{
	POINT* position;
	int playerID;
	UnitGroupLogic* army;
};

#endif
