#include <iostream>
#include <string>
#include "Server.h"

Server* server;
void OnNewMessage(SOCKET s,short id,vector<char> data)
{
	std::cout<<"Client mit ID "<<s<<" hat folgendes gesendet:\nID:"<<id<<"\nData:\n";
	for(unsigned int i=0;i<data.size();i++)
		std::cout<<data[i];
	std::cout<<"\nEnde Packet\n\n";

	if(id>=0)
		if(id == 42)
			server->write(s,2,data);
}

void Error(SOCKET s,int id, std::string msg)
{
	if(s==NULL)
		std::cout<<"SERVER-";
	else
		std::cout<<"CLIENT ID "<<s<<"-";
	std::cout << "ERROR: "<<id<<" Message: " << msg << "\n";
}

int main()
{
	server = Server::get();
	server->newMessageCallback.push_back(OnNewMessage);
	server->newMessageCallback.push_back(OnNewMessage2);
	server->errorCallback.push_back(Error);
	server->startListening();
	
	getchar();

	delete server;
}