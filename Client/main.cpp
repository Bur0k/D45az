#include <iostream>
#include <SFML\Graphics.hpp>
#include "Client.h"
#include "Game.h"

#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "NetworkParticipant.h"
#include "NetworkLogin.h"
#include "Lobby.h"

#include "MusikSampler.h"

#include "Map.h"

#include "Lobby.h"


//DEBUG DEFINES IF DEFINED ENABLED

//#define BURAKTESTSHIT



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
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR szCmdLine,int iCmdShow ) //Release Mode verwenden wir Windows als SubSystem
#else
int main()//Im Debug Mode verwenden wir Console als SubSystem. Es wird trotzdem das SFML Fenster erzeugt.
#endif
{
	//********** BURAKS CLIENT TEST SHIT
#ifdef BURAKTESTSHIT
	Client* c = Client::get();
	c->addToErrorCallback(&tc);
	c->addToNewMessageCallback(&tc);
	c->connectToServer("localhost",4242);
	c->beginRead();std::vector<char> testData;
	Client::get()->write(0,testData);

	
	
	NetworkLogin NL1("Burak");
	while(NL1.getState() == 0)//Wartet bis ne Nachricht vom Server gekommen ist. Also ob der Name verfügbar oder nicht ist
	{
	}
	cout << "NL1:" << NL1.getState() << endl;

	Lobby lobby("Burak");
	lobby.askforLobbyData();
	lobby.createNewGameLobby();
	while(lobby.gameLobby==NULL)
		;
	lobby.gameLobby->disconnect();


#endif //BURAKTESTSHIT	
	//********** BURAKS CLIENT TEST SHIT END


	cout << endl << "Hallo D45az" << endl << "oeffne Fenster" << endl;

	// create the window
	sf::RenderWindow window(sf::VideoMode(1280, 850), "D45az finezt");
	window.setPosition(sf::Vector2i(400,0));
	window.setMouseCursorVisible(true);

	// Musik Test Zeug
	/*
	MusikSampler* MS = new MusikSampler();
	
	MS->load_music(0);
	MS->play_music();
	*/


	//testausgabe
	/*

	*/
	
	
	Game g = Game(&window, TESTSCREEN, sf::Vector2f(1280, 850));
	
	
	while (window.isOpen())
	{ 
		g.Input();

		g.timer();

		// clear the window with black 
		window.clear(sf::Color::Black);
		
		g.Draw();

		// end the current frame
		window.display();
	}
	g.onClose();
	
	delete Client::get();
	MyFonts::deleteFonts(); //TODO in game implementieren

	return 0;
}
