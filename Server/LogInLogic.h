#ifndef LOGINLOGIC_H
#define LOGINLOGIC_H

#include <vector>
#include "User.h"
#include <string>

using namespace std;



class LogInLogic
{
	private:
		vector<User*> connectedUsers;

	public:
		LogInLogic(); // anmelden
		~LogInLogic();

		void connect();

		
};


#endif