#include "Unit.h"


Unit::Unit(Vector2f pos, UnitTypes Type, int Amount)
{
	
	m_type = Type;

	m_clicked = false;

	m_dimensions.left = pos.x;
	m_dimensions.top = pos.y;
	m_dimensions.width = UNIT_WIDTH;
	m_dimensions.height = UNIT_HEIGHT;
	

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
		break;
	}


	Image img;
	if(!img.loadFromFile(path))
		std::cout<< "Unit.cpp : load Image  " << path << " failed " << std::endl;

	m_UnitImage.t.loadFromImage(img);
	m_UnitImage.t.setSmooth(true);
	m_UnitImage.s.setTexture(& m_UnitImage.t);
	m_UnitImage.s.setSize(Vector2f(UNIT_WIDTH,UNIT_HEIGHT));
	m_UnitImage.s.setPosition(m_dimensions.left, m_dimensions.top);


	m_textbg.setFillColor(MyColors.WhiteTransparent);
	m_textbg.setPosition(pos.x, pos.y + UNIT_HEIGHT - 35);
	m_textbg.setSize(Vector2f(UNIT_WIDTH, 35));

	m_numberOfSoldiersText.setFont(MyFonts::getFont(GameFonts::ARIAL));
	m_numberOfSoldiersText.setCharacterSize(20);
	m_numberOfSoldiersText.setColor(MyColors.Black);


	setNumberOfSoldiers(Amount);

}

Unit::~Unit()
{

}

int Unit::getNumberOfSoldiers()
{
	return m_numberOfSoldiers;
}

void Unit::setNumberOfSoldiers(int Amount)
{
	m_numberOfSoldiers = Amount;

	m_numberOfSoldiersText.setString(std::to_string(m_numberOfSoldiers));

	Rect<float> textsize = m_numberOfSoldiersText.getLocalBounds();

	m_numberOfSoldiersText.setPosition(m_dimensions.left + (UNIT_WIDTH - textsize.width) / 2, m_dimensions.top + UNIT_HEIGHT - 30);
}

Vector2f Unit::getPosition()
{
	return Vector2f(m_dimensions.left, m_dimensions.top);
}

void Unit::setPosition(Vector2f pos)
{
	move(Vector2f(pos.x - m_dimensions.left, pos.y - m_dimensions.top));
}

void Unit::move(Vector2f delta)
{
	m_UnitImage.s.move(delta);
	m_numberOfSoldiersText.move(delta);
	m_textbg.move(delta);
	m_dimensions.left += delta.x;
	m_dimensions.top += delta.y;
}


void Unit::draw(sf::RenderWindow* rw)
{
	rw->draw(m_UnitImage.s);
	rw->draw(m_textbg);
	rw->draw(m_numberOfSoldiersText);
}

bool Unit::MouseMoved(sf::Vector2i & mouse)
{
	if( mouse.x >= m_dimensions.left && mouse.x <= m_dimensions.left + m_dimensions.width &&
		mouse.x >= m_dimensions.left && mouse.x <= m_dimensions.left + m_dimensions.width)
		m_mouseOver = true;
	else
		m_mouseOver = false;

	return m_mouseOver;
}

bool Unit::PressedLeft()
{
	if(m_mouseOver)
	{
		m_clicked = !m_clicked;
		if(m_clicked)	
			m_textbg.setFillColor(MyColors.BlueTransparent);
		else 
			m_textbg.setFillColor(MyColors.WhiteTransparent);
		return true;
	}
	return false;
}


//theese do nothing for now
bool Unit::PressedRight(){return false;}
bool Unit::ReleasedRight(){return false;}
bool Unit::ReleasedLeft(){return false;}