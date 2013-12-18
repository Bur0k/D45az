#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User
{
	private:
		string name;

	public:
		User();
		User(string name);
		~User();

		string getName();
		void setName(string name);
};

#endif