#ifndef BUTTON_H
#define BUTTON_H

#include <SFML\Graphics.hpp>
#include <vector>
#include "IDrawable.h"


typedef std::vector<void (*) (void)> FuncPointerVect;

// implements basic button functionality
// derived classes should implement visuals
class Button : public IDrawable
{
protected:
	sf::Vector2f size;
	sf::Vector2f position;
	FuncPointerVect attachedFunctions;
	bool isEnabled;
	//to avoid spamming attached functions
	bool isClicked;

public:
	Button(sf::Vector2f size, sf::Color c);
	~Button();

	//implementing IDrawable
	virtual void draw(sf::RenderWindow* rw);

	bool isHit(sf::Vector2f);

	//attaching a function pointer 
	bool attachFunction(void (*pfunc)(void));
	//detaching a function pointer
	bool detachFunction(void (*pfunc)(void));

};


#endif