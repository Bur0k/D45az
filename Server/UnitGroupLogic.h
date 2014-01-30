#ifndef UNITGROUPLOGIC_H
#define UNITGROUPLOGIC_H

#include "NetworkParticipant.h"
#include "Server.h"
#include "UnitLogic.h"
#include <math.h>
#include <vector>

using namespace std;

class UnitGroupLogic
{
private:
	Server* server;

public:

	vector<UnitLogic*> units;
	vector<UnitGroupLogic*>* unitGroups;
	
	POINT pos;


public:
	UnitGroupLogic(short units, UnitTypes type, POINT p, vector<UnitGroupLogic*>* unitGroups);
	~UnitGroupLogic();

	void moveOneStep(POINT to);
	void addUnit(short units, UnitTypes type);
	void removeUnit(short units, UnitTypes type); 
	void move(POINT moves[], int arrlen);
	void splitandMove(short units[], UnitTypes types[], POINT moves[], int arrlen);


	void processNewMessage(SOCKET s,short id,std::vector<char> data);
	void processNetworkError(SOCKET s,int errCode,std::string errMessage);

};

#endif