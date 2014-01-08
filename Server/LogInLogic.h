#ifndef LOGINLOGIC_H
#define LOGINLOGIC_H

#include <vector>
#include "PlayerData.h"
#include <string>
#include "Server.h"
#include "NetworkParticipant.h"

using namespace std;

class LogInLogic : public NetworkParticipant
{
private:
	Server* server;


public:
	LogInLogic(); // anmelden
	~LogInLogic();

	static void LogicMessageCallback(SOCKET s,short id,vector<char> data);

	void processNewMessage(SOCKET s,short id,std::vector<char> data);
	void processNetworkError(SOCKET s,int errCode,std::string errMessage);
};

#endif