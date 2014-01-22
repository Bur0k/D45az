#ifndef MENUVIEW_H
#define MENUVIEW_H

#include <SFML/Graphics.hpp>
#include <math.h>

#include "iview.h"
#include "graphic_globals.h"
#include "StandardButton.h"
#include "Slider.h"
#include "Textblock.h"

using namespace sf;

#define MENU_ANIMATIONTIME 30
#define MENU_WIDTH 200
#define MENU_BORDERSPACING 20

class MenuView : public IView, public IButtonfunction, public ISliderFunction
{
private:
	//in case we need an extended version of the menu
	bool m_extended;
	bool m_animating;
	int backgroundanimation;
	Views m_nextView;

	RectangleShape m_background;
	SpriteTex* m_pGraphics;

	Button* m_exitbutton;
	Button* m_continuebutton;
	Textblock* m_volumetext;
	Slider* m_volumeslider;

	DrawVect m_DrawV;
	AnimateVect m_AnimateV;
	ClickVect m_ClickV;
	KeyInputVect m_KeyV;

public:
	MenuView(Vector2u & screensize, bool extended);
	~MenuView(void);

	virtual Views nextState();
	//implementing a lot of interfaces

	

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
	virtual void pt1zyklisch(double elpasedMs);

	virtual Views getType();



	virtual void onButtonClick(int);

	virtual void onSliderValueChange(int ID, double position);
	virtual void onSliderReleased(int ID, double position);

private:
	void positionElements(Vector2u & size);
};

#endif //MENUVIEW_H