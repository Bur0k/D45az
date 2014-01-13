#ifndef IKEYBOARDINPUT_H
#define IKEYBOARDINPUT_H

#include <SFML\Graphics.hpp>
#include <vector>

class IKeyboardinput
{
public:
	virtual void onKeyDown(sf::Event)=0;
	virtual void onKeyUp(sf::Event)=0;
	virtual void onTextInput(std::string s)=0;
};

typedef std::vector<IKeyboardinput*>KeyInputVect;

#endif