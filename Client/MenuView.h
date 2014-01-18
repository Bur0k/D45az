#ifndef MENUVIEW_H
#define MENUVIEW_H

#include <SFML/Graphics.hpp>
#include "iview.h"
#include "graphic_globals.h"
#include "StandardButton.h"
#include <math.h>

using namespace sf;

#define MENUANIMATIONTIME 30

class MenuView : public IView, public IButtonfunction
{
private:
	bool m_animating;
	int backgroundanimation;
	Views m_nextView;

	RectangleShape m_background;
	
	SpriteTex* m_pGraphics;
	Button* m_exitbutton;
	Button* m_continuebutton;

	DrawVect m_DrawV;
	AnimateVect m_AnimateV;
	ClickVect m_ClickV;
	KeyInputVect m_KeyV;

public:
	MenuView(Vector2u & screensize);
	~MenuView(void);

	virtual Views nextState();
	//implementing a lot of interfaces

	virtual void onButtonClick(int);

	virtual void draw(sf::RenderWindow* rw);

	virtual bool MouseMoved(sf::Vector2i &);
	virtual bool PressedRight();
	virtual bool PressedLeft();
	virtual bool ReleasedRight();
	virtual bool ReleasedLeft();
	
	virtual void animationTick(); 
	
	virtual void onKeyDown(sf::Event);
	virtual void onKeyUp(sf::Event);
	virtual void onTextInput(std::string s);

	virtual void onResize(sf::Vector2u &);
	virtual void update(double elpasedMs);

	virtual Views getType();

private:
	void centering(Vector2u & size);
};

#endif //MENUVIEW_H