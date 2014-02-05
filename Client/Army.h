#ifndef ARMY_H
#define ARMY_H

#include <SFML\Graphics.hpp>
#include <vector>
#include "graphic_globals.h"
#include "IClickable.h"
#include "IKeyboardInput.h"
#include "IAnimatable.h"
#include "IDrawable.h"
#include "UnitGroup.h"
#include "SplittedSprite.h"

using namespace sf;

#define ARMY_ANIMATIONSTEPS 10
#define ARMY_SPRITE_WIDTH 62
#define ARMY_SPRITE_HEIGHT 64
#define ARMY_POWERBAR_THICKNESS 5

#define ARMY_TILESIZE 64

class Army
	: public IDrawable, public IClickable, public IAnimatable, public IIngameObjects
{
private:
	int m_playerID;
	bool m_mouseOver;

	//animation variables;
	int m_animation;
	Vector2f m_a_oldPos;
	Vector2f m_a_targetPos;

	//if army is in a city only its power flag will be drawn
	bool m_inCity;
	
	Vector2i m_position;
	Rect<float> m_dimensions;


	CircleShape m_markedIndicator;
	Color m_playerColor;
	Sprite m_body; // TODO buraks klasse anwenden
	RectangleShape m_powerBar;
	RectangleShape m_pBarBg;

	Texture* m_texture;
	SplittedSprite* m_armySprite;
	//62 breit 64 hoch

	void PositionGraphics();
	Army();
public:
	std::vector<Vector2i> moves;
	UnitGroup* units;

	int getPlayerID();

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

	//IInagameObject
	ingameObjectType getType();
	void onMapMove(Rect<int>);
	
	void setPower(float power);

	//if army is in the fow
	bool m_isVisible;

	bool m_marked;
	bool m_animating;
	
	Vector2i m_mapViewOffset;
	Vector2i m_Tilesize;
	

	Army(UnitGroup* ug, Rect<int> & mapView, bool isVisible, bool isIncCity);
	~Army();

	

	Vector2i getPosition();
	//immediately sets the position of the army
	void setPosition(Vector2i);
	//moves the army with an animation of x ticks to position
	void move(Vector2i);
	bool animatedMove(Vector2i);

	Army* split(int seletion, std::vector<UnitGroup> & newUnits);

};


#endif //ARMY_H