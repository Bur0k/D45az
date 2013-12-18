#ifndef LOGINLOGIC_H
#define LOGINLOGIC_H

#include <vector>
#include "User.h"
#include <string>
#include "Server.h"

using namespace std;

class LogInLogic
{
	private:
		vector<User*> connectedUsers;
		Server* server;

		static LogInLogic* self;

	public:
		LogInLogic(); // anmelden
		~LogInLogic();

		static void LogicMessageCallback(SOCKET s,short id,vector<char> data);
};

#endif