#include "Slider.h"



Slider::Slider(bool horizontal, Vector2f size, double startsliderposition, Vector2f pos, int id)
{	
	m_horizontal = horizontal;
	m_size = size;
	m_position = pos;
	m_ID = id;

	m_dimensions.left = pos.x;
	m_dimensions.top = pos.y;

	m_dimensions.height = size.y;
	m_dimensions.width = size.x;
	
	m_pBar = new SpriteTex[4];

	//load textures...
	//TODO

	//place objects

	if(m_horizontal)
	{
		m_pBar[0].s.setSize(Vector2f(SLIDERENDBLOCKWIDTH, size.y));	//left knob
		m_pBar[0].s.setPosition(pos.x,pos.y);
		m_pBar[1].s.setSize(Vector2f(SLIDERENDBLOCKWIDTH, size.y)); //right knob
		m_pBar[1].s.setPosition(pos.x + size.x -  SLIDERENDBLOCKWIDTH * 2, pos.y);
		m_pBar[2].s.setSize(Vector2f(size.x - SLIDERENDBLOCKWIDTH * 2, size.y / 3)); //slider Bar
		m_pBar[2].s.setPosition(pos.x + SLIDERENDBLOCKWIDTH, pos.y + size.y / 3); 
		m_pBar[3].s.setSize(Vector2f(size.y, size.y)); //slider
		m_pBar[3].s.setPosition(pos.x + SLIDERENDBLOCKWIDTH + startsliderposition * (size.x - SLIDERENDBLOCKWIDTH * 2 - size.y), pos.y);
	}
	else
	{
		//TODO
	}

	for(unsigned int i = 0; i < 4; i++)
		m_pBar[i].s.setFillColor(MyColors.White);
	
}

Slider::~Slider()
{
	delete[] m_pBar;
}

double Slider::getValue()
{
	return 0;
}

void setPosition(Vector2f)
{

}

Vector2f getPosition()
{
	return Vector2f(2,2);
}

void move(Vector2f)
{

}

void Slider::Notify()
{

}

void Slider::Attach(ISliderFunction*)
{

}

bool Slider::Detach(ISliderFunction*)
{
	return false;
}

bool Slider::isHit(sf::Vector2i & mouse)
{
	//check if mouse is on slider

	if( m_pBar[3].s.getPosition().x < mouse.x && m_pBar[3].s.getPosition().x + m_pBar[3].s.getSize().x > mouse.x &&
		m_pBar[3].s.getPosition().y < mouse.y && m_pBar[3].s.getPosition().y + m_pBar[3].s.getSize().y > mouse.y)
	{
		m_mouseOver = true;
		std::cout << "Slider ID: " << m_ID << std::endl;
		if(m_mouseDown)
		{	
			if(m_horizontal)
			{
				float delta = mouse.x - m_pBar[3].s.getPosition().x;
				std::cout << "Slider Mouse Delta :  x " << delta << std::endl;
				m_pBar[3].s.setPosition(mouse.x + delta , m_pBar[3].s.getPosition().y); 

			}
		}

	}
	else
		m_mouseOver = false;

	//move slider
	
	return m_mouseOver;
}

void Slider::PressedRight(){}
void Slider::ReleasedRight(){}

void Slider::PressedLeft()
{
	if(m_mouseOver)
		m_mouseDown = true;
	else 
		m_mouseDown = false;

	//TODO notify
}

void Slider::ReleasedLeft()
{
	//TODO notify
}

void Slider::draw(RenderWindow* rw)
{
	for(int i = 0; i < 4; i++)
		rw->draw(m_pBar[i].s);
}