#include <iostream>
#include <SFML\Graphics.hpp>
#include "Client.h"
#include "Game.h"

#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "NetworkParticipant.h"
#include "Lobby.h"
#include "LobbyView.h"

#include "MusikSampler.h"

#include "Map.h"

#include "Lobby.h"



PlayerData playerData;


using namespace std;

class testClient : public NetworkParticipant
{
	void processNewMessage(short id,vector<char> data)
	{
		std::cout<<"Server hat folgendes gesendet:\nID:"<<std::hex<<(int)id<<"\nData:\n";
		for(unsigned int i=0;i<data.size();i++)
			std::cout<<std::hex<<(int)data[i]<<" ";
		std::cout<<"\nEnde Packet\n\n";
	}

	void processNetworkError(int id, std::string msg)
	{
		std::cout << "ERROR: "<<std::hex<<(int)id<<" Message: " << msg << "\n";
	}
} tc;

#ifndef _DEBUG
int main()//int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR szCmdLine,int iCmdShow ) //Release Mode verwenden wir Windows als SubSystem
#else
int main()//Im Debug Mode verwenden wir Console als SubSystem. Es wird trotzdem das SFML Fenster erzeugt.
#endif
{
	Client* c = Client::get();
	c->addToErrorCallback(&tc);
	c->addToNewMessageCallback(&tc);



	cout << endl << "Hallo D45az" << endl << "oeffne Fenster" << endl;

	// create the window
	sf::RenderWindow window(sf::VideoMode(1280, 850), "D45az finezt");
	window.setPosition(sf::Vector2i(400,0));
	window.setMouseCursorVisible(false);



	//erlaubte einstiegspunkte für Views::
	//TESTSCREEN LOGIN LOBBY
	Game* g = new Game(&window, Views::LOGIN, sf::Vector2f(1280, 850));
	
	
	while (window.isOpen())
	{
		g->Input();

		g->timer();

		window.clear(sf::Color::Black);
		
		g->Draw();
		
		window.display();
	}
	
	delete g;
	
	delete Client::get();

	MyFonts::deleteFonts(); //TODO in game implementieren

	return 0;
}
