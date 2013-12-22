#include <iostream>
#include <SFML\Graphics.hpp>
#include "Client.h"
#include "Game.h"
#include "Jans_Abgeher_Shit.h"

#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "NetworkParticipant.h"

using namespace std;

class testClient : public NetworkParticipant
{
	void processNewMessage(short id,vector<char> data)
	{
		std::cout<<"Server hat folgendes gesendet:\nID:"<<id<<"\nData:\n";
		for(unsigned int i=0;i<data.size();i++)
			std::cout<<data[i];
		std::cout<<"\nEnde Packet\n\n";
	}

	void processNetworkError(int id, std::string msg)
	{
		std::cout << "ERROR: "<<id<<" Message: " << msg << "\n";
	}
} tc;

void OnNewMessage(short id,vector<char> data)
{
	std::cout<<"ID:"<<id<<"\nData:\n";
	for(unsigned int i=0;i<data.size();i++)
		std::cout<<data[i];
	std::cout<<"\nEnde Packet\n\n";

}

void jans_test_karre()
{
	Music music;
	string status;

	if (music.openFromFile("test.ogg"))
	{
		cout << "passt" << endl << endl;
		music.play();
	}

	music.setVolume(90);

	status = music.getStatus() ;

	cout << music.getStatus() << endl;
}

#ifndef _DEBUG
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR szCmdLine,int iCmdShow ) //Release Mode verwenden wir Windows als SubSystem
#else
int main()//Im Debug Mode verwenden wir Console als SubSystem. Es wird trotzdem das SFML Fenster erzeugt.
#endif
{
	//********** BURAKS CLIENT TEST SHIT
	Client* c = Client::get();
	c->addToErrorCallback(&tc);
	c->addToNewMessageCallback(&tc);
	c->connectToServer("localhost",4242);
	c->beginRead();std::vector<char> testData;
	Client::get()->write(0,testData);
	testData.push_back('H');
	testData.push_back('i');
	testData.push_back('!');
	testData.push_back('\0');
	Client::get()->write(42,testData);
	Client::get()->write(42,testData);
	//********** BURAKS CLIENT TEST SHIT END


	cout << "Hallo D45az" << endl;
	cout << "oeffne Fenster" << endl;

	// create the window
	sf::RenderWindow window(sf::VideoMode(1280, 850), "45azFinezt");
	window.setPosition(sf::Vector2i(400,0));



	Game g(& window, Testscreen, sf::Vector2f(1280, 850));

	jans_test_karre();




	while (window.isOpen())
	{ 

		if(!g.Input())
			break;

		g.timer();


		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		// window.draw(...);

		g.Draw();


		// end the current frame
		window.display();
	}


	delete c;
	return 0;
}
