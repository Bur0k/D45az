#include <iostream>
#include <SFML\Graphics.hpp>
#include "Client.h"
#include "Jans_Abgeher_Shit.h"

using namespace std;


void OnNewMessage(short id,vector<char> data)
{
	std::cout<<"ID:"<<id<<"\nData:\n";
	for(unsigned int i=0;i<data.size();i++)
		std::cout<<data[i];
	std::cout<<"\nEnde Packet\n\n";

}

#ifndef _DEBUG
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR szCmdLine,int iCmdShow ) //Release Mode verwenden wir Windows als SubSystem
#else
int main()//Im Debug Mode verwenden wir Console als SubSystem. Es wird trotzdem das SFML Fenster erzeugt.
#endif
{
	cout << "Hallo D45az" << endl;
	cout << "oeffne Fenster" << endl;
	 // create the window
    sf::RenderWindow window(sf::VideoMode(1280, 850), "primePatterns");
	
	//window.setSize(sf::Vector2u (900,900));
	window.setPosition(sf::Vector2i(400,0));

	sf::Font font = sf::Font();
	if(!font.loadFromFile("Data/Fonts/arial.ttf"))
	{
		cout << "font load failed!" << endl;
	}
	else
		cout << "font load successful!" << endl;

	sf::Text t = sf::Text();
	t.setString("Hallo Welt \n D45az finezt.");
	t.setPosition(sf::Vector2f(200,200));
	t.setFont(font);
	t.setColor(sf::Color::White);

	sf::RectangleShape r = sf::RectangleShape();
	r.setPosition(sf::Vector2f(200,400));
	r.setSize(sf::Vector2f(50,50));
	r.setFillColor(sf::Color::Blue);
	
	window.draw(t);


	while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

			//closes the window on escape
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
        }
		


        // clear the window with black color
		window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);
		
		

		window.draw(t);
		window.draw(r);


		
		
	

        // end the current frame
        window.display();
    }


	
	return 0;
}