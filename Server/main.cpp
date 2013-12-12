#include <iostream>
#include "Server.h"

void OnNewMessage(ClientHandler* ch,short id,vector<char> data)
{
	std::cout<<"Client mit ID "<<ch->s<<" hat folgendes gesendet:\nID:"<<id<<"\nData:\n";
	for(unsigned int i=0;i<data.size();i++)
		std::cout<<data[i];
	std::cout<<"\nEnde Packet\n\n";

	if(id>=0)
		ch->write(2,data);
}

void Error(ClientHandler* ch,int id, std::string s)
{
	if(ch==NULL)
		std::cout<<"SERVER-";
	else
		std::cout<<"CLIENT ID "<<ch->s<<"-";
	std::cout << "ERROR: "<<id<<" Message: " << s << "\n";
}

int main()
{
	Server* s = new Server();
	s->newMessageCallback.push_back(OnNewMessage);
	s->errorCallback.push_back(Error);
	s->startListening();
	
	getchar();

	delete s;
}