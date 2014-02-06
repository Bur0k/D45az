#ifndef UNITGROUP_H
#define UNITGROUP_H

#define maxlivingsoldiers 25

#define light 2.0
#define heavy 2.4
#define longrange 2.8
#define artillery 3.0

#define def 1.2
#define off 1
#define run -1

#define maxstrength (16 * maxlivingsoldiers * artillery * def)

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