#ifndef UNITGROUPLOGIC_H
#define UNITGROUPLOGIC_H

#include "NetworkParticipant.h"
#include "Server.h"
#include "UnitLogic.h"
#include <vector>

using namespace std;

class UnitGroupLogic
{
private:
	Server* server;

public:
	UnitGroupLogic();
	~UnitGroupLogic();

	vector<UnitLogic>troops;

	void processNewMessage(SOCKET s,short id,std::vector<char> data);
	void processNetworkError(SOCKET s,int errCode,std::string errMessage);

};

#endif