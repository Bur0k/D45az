#include "Unit.h"


Unit::Unit(UnitTypes Type, int Amount)
{

}

Unit::~Unit()
{

}

int Unit::getNumberOfSoldiers(){return 1;}
void Unit::setNumberOfSoldiers(int){}

Vector2f Unit::getPosition(){return Vector2f(0,0);}
void Unit::setPosition(Vector2f){}
void Unit::move(Vector2f){}


void Unit::draw(sf::RenderWindow* rw){}

bool Unit::MouseMoved(sf::Vector2i &)
{
	return false;
}

bool Unit::PressedLeft()
{
	return false;
}


//theese do nothing for now
bool Unit::PressedRight(){return false;}
bool Unit::ReleasedRight(){return false;}
bool Unit::ReleasedLeft(){return false;}