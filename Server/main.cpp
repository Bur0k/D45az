#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Server.h"
#include "NetworkParticipant.h"
#include "LogInLogic.h"
#include "LobbyLogic.h"
#include "Map.h"

Server* server;

class testServer : public NetworkParticipant
{
	void processNewMessage(SOCKET s,short id,vector<char> data)
	{
		std::cout<<"Client mit ID "<<s<<" hat folgendes gesendet:\nID:"<<std::hex<<(int)id<<"\nData:\n";
		for(unsigned int i=0;i<data.size();i++)
			std::cout<<std::hex<<(int)data[i]<<" ";
		std::cout<<"\nEnde Packet\n\n";
	}

	void processNetworkError(SOCKET s,int id, std::string msg)
	{
		if(s==NULL)
			std::cout<<"SERVER-";
		else
			std::cout<<"CLIENT ID "<<s<<"-";
		std::cout << "ERROR: "<<std::hex<<(int)id<<" Message: " << msg << "\n";
	}
};

int main()
{
	srand((unsigned int)time(NULL)); // #Karre

	Map map;
	map.load("Data/Maps/TestMap.tmx");
	

	testServer* ts = new testServer();

	server = Server::get();
	server->addToNewMessageCallback(ts);

	server->startListening();

	LogInLogic* LIL = new LogInLogic();
	LobbyLogic* LL = new LobbyLogic();

	getchar();

	delete LIL;
	delete LL;
	delete ts;
	delete server;
}