#include <iostream>
#include "Server.h"

int main()
{
	Server* s = new Server();
	s->startListening();
	while(true);
}