#ifndef UNITGROUPLOGIC_H
#define UNITGROUPLOGIC_H

#include "NetworkParticipant.h"
#include "Server.h"
#include "UnitLogic.h"
#include <math.h>
#include <vector>



//#define def 1.2
//#define off 1
//#define run -1

using namespace std;

static const float run = -0.3f;
static const float off = 0.8f;
static const float def = (float)1.1;

enum class UnitStrategy{DEFENSIVE, OFFENSIVE, RUNNING};

class UnitGroupLogic
{
private:
	Server* server;

public:

	vector<UnitLogic*> units;
	vector<UnitGroupLogic*>* unitGroups;

	UnitStrategy strategy;
	
	POINT* pos;
	short player_ID;


public:
	UnitGroupLogic(short units, UnitTypes type, POINT p, vector<UnitGroupLogic*>* unitGroups);
	~UnitGroupLogic();

	bool mergeUnitGroup(UnitGroupLogic* unitgroup);
	void addUnit(short living, UnitTypes type);
	
	//out of date
	void moveOneStep(POINT to);
	void removeUnit(short units, UnitTypes type); 
	void move(POINT moves[], int arrlen);
	void splitandMove(short units[], UnitTypes types[], POINT moves[], int arrlen);
	void changeStrategy(UnitStrategy strategy);


	void processNewMessage(SOCKET s,short id,std::vector<unsigned char> data);
	void processNetworkError(SOCKET s,int errCode,std::string errMessage);
};

#endif