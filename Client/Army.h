#ifndef ARMY_H
#define ARMY_H

#include <SFML\Graphics.hpp>
#include "graphic_globals.h"
#include "IClickable.h"
#include "IKeyboardInput.h"
#include "IAnimatable.h"
#include "IDrawable.h"

using namespace sf;

#define ARMY_ANIMATIONSTEPS 10

class Army
	: public IDrawable, public IClickable, public IAnimatable
{
private:
	
	bool m_mouseOver;
	int m_animation;
	Vector2f m_oldPos;

	//if army is in a city only its power flag will be drawn
	bool m_inCity;
	Vector2i m_position;
	Rect<float> m_dimensions;

	CircleShape m_markedIndicator;
	Sprite m_body; // TODO buraks klasse anwenden
	RectangleShape m_powerBar;
	Sprite m_flag;
	
	
	//IDrawable
	void draw(sf::RenderWindow* rw);
	//IClickable
	bool MouseMoved(sf::Vector2i &);
	bool PressedRight();
	bool PressedLeft();
	bool ReleasedRight();
	bool ReleasedLeft();
	//IAnimatable
	void animationTick();

	//ArmyObject from space	

public:
	bool m_marked;
	bool m_animating;

	Vector2i m_mapViewOffset;
	Vector2i m_Tilesize;
	
	Army();
	Army(int i);
	~Army();

	

	Vector2i getPosition();
	//immediately sets the position of the army
	void setPosition(Vector2i);
	//moves the army with an animation of x ticks to position
	void move(Vector2i);

};


#endif //ARMY_H