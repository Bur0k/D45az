#ifndef IKEYBOARDINPUT_H
#define IKEYBOARDINPUT_H

#include <SFML\Graphics.hpp>

class IKeyboardinput
{
public:
	virtual void onKeyDown(sf::Event)=0;
	virtual void onKeyUp(sf::Event)=0;
};


#endif