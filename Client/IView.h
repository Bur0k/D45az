#ifndef IVIEW_H
#define IVIEW_H

#include "IDrawable.h"
#include "IClickable.h"
#include "IAnimatable.h"
#include "IKeyboardInput.h"
#include "Game.h"


enum ScreenMode {Ingame, Login, Menue, Lobby, IngameMenu, Testscreen};


typedef void (*changeView_func)(ScreenMode);

//unites all gui Interfaces for Model View Controller Implementation
class IView 
	: public IDrawable, public IClickable, public IAnimatable, public IKeyboardinput
{
protected:
	changeView_func m_callbackFunc;
	virtual void cangeView()=0;
};

#endif