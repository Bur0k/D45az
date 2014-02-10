#ifndef UNITLOGIC_H
#define UNITLOGIC_H

//#define light 2.0
//#define heavy 2.4
//#define longrange 2.8
//#define artillery 3.0

//#define maxlivingsoldiers 25
static const  int maxlivingsoldiers = 25;

static const float light = (float)2.0;
static const float heavy = (float)2.4;
static const float longrange = (float)2.8;
static const float artillery = (float)3.0;

#include "NetworkParticipant.h"
#include "Server.h"

using namespace std;

enum class UnitTypes{LIGHT, HEAVY, LONGRANGE, ARTILLERY};


class UnitLogic
{

public:
	UnitLogic(UnitTypes type);
	~UnitLogic();

	UnitTypes type;

	short living; // 25 Einheiten
	int range;
	double attackpower;
};

#endif