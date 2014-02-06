#ifndef UNIT_H
#define UNIT_H

#include <SFML\Graphics.hpp>
#include "IDrawable.h"
#include "IClickable.h"
#include "graphic_globals.h"


//#define UNIT_WIDTH 60
//#define UNIT_HEIGHT 90

static const float UNIT_WIDTH = 60.0f;
static const float UNIT_HEIGHT = 90.0f;

using namespace sf;

enum class UnitStrategy{DEFENSIVE, OFFENSIVE, RUNNING};
enum class UnitTypes{LIGHT, HEAVY, LONGRANGE, ARTILLERY};

class Unit : public IDrawable, public IClickable
{
private:

	Rect<float> m_dimensions;
	SpriteTex m_UnitImage;
	Text m_numberOfSoldiersText;

	int m_numberOfSoldiers;
	UnitTypes m_type;
	RectangleShape m_textbg;
	bool m_mouseOver;

public:
	bool m_clicked;
	Unit(Vector2f pos, UnitTypes Type, int Amount);
	~Unit();

	int getNumberOfSoldiers();
	void setNumberOfSoldiers(int);

	Vector2f getPosition();
	void setPosition(Vector2f);
	void move(Vector2f);

	//implementing interfaces

	void draw(sf::RenderWindow* rw);

	bool MouseMoved(sf::Vector2i &);
	bool PressedRight();
	bool PressedLeft();
	bool ReleasedRight();
	bool ReleasedLeft();

private:
	
};




#endif //UNIT_H