#include "Unit.h"


Unit::Unit(UnitTypes Type, int Amount)
{
	m_numberOfSoldiers = Amount;
	m_type = Type;

	std::string path;
	path = "Data/Images/";

	switch (m_type)
	{
	case UnitTypes::LIGHT:
		path += "unit_light.png";
		break;
	case UnitTypes::HEAVY:
		path += "unit_heavy.png";
		break;
	case UnitTypes::LONGRANGE:
		path += "unit_ranged.png";
		break;
	case UnitTypes::ARTILLERY:
		path += "unit_artillery.png";
		break;
	default:
		std::cout<< "unit.cpp: unknown unit!!!"; 
		break;
	}
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