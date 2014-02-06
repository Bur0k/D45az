#ifndef UNITGROUP_H
#define UNITGROUP_H

//#define maxlivingsoldiers 25

//#define light 2.0
//#define heavy 2.4
//#define longrange 2.8
//#define artillery 3.0

static const int maxlivingsoldiers = 25;

static const float light = (float)2.0;
static const float heavy = (float)2.4;
static const float longrange = (float)2.8;
static const float artillery = (float)3.0;

static const float def____ = (float)1.2;
static const float off____ = (float)1;
static const float run____ = (float)-1;

static const float maxstrength = (16 * maxlivingsoldiers * artillery * def____);

#include "NetworkParticipant.h"
#include "Client.h"
#include "Unit.h"
#include "Ingame.h"
#include "City.h"

struct soldiers
{
	short count;
	UnitTypes type;
};


class UnitGroup : public NetworkParticipant
{
private:

	Client* c;

public:
	POINT pos;
	short player_ID;
	soldiers* units;

	UnitStrategy strategy;

	UnitGroup(POINT pos, UnitTypes types[16], short livingsoldiers[16], UnitStrategy strategy, City* producer);
	~UnitGroup();

	void processNewMessage(short id,vector<char> data);
	void processNetworkError(int id, std::string msg);
	float getUnitgroupStrength();
};



#endif