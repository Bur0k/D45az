#ifndef CITYLOGIC_H
#define CITYLOGIC_H

#include "NetworkParticipant.h"
#include <vector>

using namespace std;

class CityLogic : public NetworkParticipant
{
private:

public:
	int level;
	//position
	int generatedIncome;
	CityLogic();
	~CityLogic();
};

#endif