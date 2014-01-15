#ifndef IVIEW_H
#define IVIEW_H

#include "IDrawable.h"
#include "IClickable.h"
#include "IAnimatable.h"
#include "IKeyboardInput.h"


enum Views {NOCHANGE, INGAME, LOGIN, MENUE, LOBBY, INGAME_MENU, TESTSCREEN};


//unites all gui Interfaces for Model View Controller Implementation
class IView 
	: public IDrawable, public IClickable, public IAnimatable, public IKeyboardinput
{
protected:
	virtual void cangeView()=0;
public:
	virtual Views nextState()=0;
};

#endif //IVIEW_H