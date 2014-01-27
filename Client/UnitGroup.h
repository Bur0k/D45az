#ifndef UNITGROUP_H
#define UNITGROUP_H

#include "NetworkParticipant.h"
#include "Client.h"
#include "Unit.h"

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

	soldiers* units;

	UnitGroup(POINT pos, short countLight, short countHeavy, short countLongrange, short countArtillery);
	~UnitGroup();

	void processNewMessage(short id,vector<char> data);
	void processNetworkError(int id, std::string msg);
};



#endif