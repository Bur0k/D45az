#ifndef BUTTON_H
#define BUTTON_H

#include <SFML\Graphics.hpp>


class Button
{
private:
	sf::Vector2f size;
	sf::Vector2f position;
public:
	Button(sf::Vector2f size, sf::Color c);
	~Button();

};


#endif