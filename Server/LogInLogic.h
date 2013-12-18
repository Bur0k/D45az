#ifndef LOGINLOGIC_H
#define LOGINLOGIC_H

#include <vector>
#include "User.h"
#include <string>
#include "ClientHandler.h"
#include "Server.h"

using namespace std;

class LogInLogic
{
	private:
		vector<User*> connectedUsers;

	public:
		LogInLogic(); // anmelden
		~LogInLogic();

		void LogicMessageCallback(ClientHandler* ch,short id,vector<char> data);
};

#endif