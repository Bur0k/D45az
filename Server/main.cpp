#include <iostream>
#include <string>
#include "Server.h"
#include "NetworkParticipant.h"

Server* server;

class testServer : public NetworkParticipant
{
	void processNewMessage(SOCKET s,short id,vector<char> data)
	{
		std::cout<<"Client mit ID "<<s<<" hat folgendes gesendet:\nID:"<<id<<"\nData:\n";
		for(unsigned int i=0;i<data.size();i++)
			std::cout<<data[i];
		std::cout<<"\nEnde Packet\n\n";

		if(id>=0)
			server->write(s,2,data);
	}

	void processNetworkError(SOCKET s,int id, std::string msg)
	{
		if(s==NULL)
			std::cout<<"SERVER-";
		else
			std::cout<<"CLIENT ID "<<s<<"-";
		std::cout << "ERROR: "<<id<<" Message: " << msg << "\n";
	}
};

int main()
{
	testServer* ts = new testServer();

	server = Server::get();
	server->addToNewMessageCallback(ts);

	server->startListening();

	getchar();

	delete ts;
	delete server;
}