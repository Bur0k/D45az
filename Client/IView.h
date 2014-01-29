#ifndef IVIEW_H
#define IVIEW_H

#include "IDrawable.h"
#include "IClickable.h"
#include "IAnimatable.h"
#include "IKeyboardInput.h"


enum class Views {NOCHANGE, INGAME, LOGIN, MENU, LOBBY, GAMELOBBY, CLOSE, TESTSCREEN};


//unites all gui Interfaces for Model View Controller Implementation
class IView 
	: public IDrawable, public IClickable, public IAnimatable, public IKeyboardinput
{
public:
	virtual ~IView(){};
	virtual void onResize(sf::Vector2u &)=0;
	virtual void update(double elapsedMs)=0;
	virtual Views nextState()=0;
	//needed for View Management in class game
	virtual Views getType()=0;
};

#endif //IVIEW_H