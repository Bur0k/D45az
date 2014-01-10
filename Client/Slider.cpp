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

	m_mouseOver = false;
	m_mouseDown = false;
	m_wasClicked = false;

	m_dimensions.width = size.x;
	m_dimensions.height = size.y;
	m_dimensions.left = pos.x;
	m_dimensions.top = pos.y;


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
		m_pBar[0].s.setSize(Vector2f(size.x, SLIDERENDBLOCKWIDTH));	//left knob
		m_pBar[0].s.setPosition(pos.x,pos.y);
		m_pBar[1].s.setSize(Vector2f(size.x, SLIDERENDBLOCKWIDTH)); //right knob
		m_pBar[1].s.setPosition(pos.x, pos.y + size.y -  SLIDERENDBLOCKWIDTH * 2);
		m_pBar[2].s.setSize(Vector2f(size.x / 3,size.y - SLIDERENDBLOCKWIDTH * 2)); //slider Bar
		m_pBar[2].s.setPosition(pos.x + size.x / 3, pos.y + SLIDERENDBLOCKWIDTH); 
		m_pBar[3].s.setSize(Vector2f(size.x, size.x)); //slider
		m_pBar[3].s.setPosition(pos.x, pos.y + SLIDERENDBLOCKWIDTH + startsliderposition * (size.y - SLIDERENDBLOCKWIDTH * 2 - size.x));
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
	double result = 0;
	if(m_horizontal)
		result = (double)(m_pBar[3].s.getPosition().x - m_dimensions.left - SLIDERENDBLOCKWIDTH) / (double)(m_dimensions.width - SLIDERENDBLOCKWIDTH * 3 - m_dimensions.height);
	else
		result = (double)(m_pBar[3].s.getPosition().y - m_dimensions.top - SLIDERENDBLOCKWIDTH) / (double)(m_dimensions.height - SLIDERENDBLOCKWIDTH * 3 - m_dimensions.width);

	return result;
}

void Slider::setPosition(Vector2f pos)
{
	Vector2f delta;
	delta.x = m_dimensions.left - pos.x;
	delta.y = m_dimensions.top - pos.y;
	//now just call move


}

Vector2f Slider::getPosition()
{
	return Vector2f(m_dimensions.left, m_dimensions.top);
}

void Slider::move(Vector2f delta)
{
	m_dimensions.left += delta.x;
	m_dimensions.top += delta.y;

	//for(int i = 0; i < )
}

void Slider::Notify()
{
	for(unsigned int i = 0; i < m_attachedFunctions.size(); i++)
	{
		if(m_mouseDown)
			m_attachedFunctions[i]->onSliderValueChange(m_ID, getValue());
		else
			m_attachedFunctions[i]->onSliderReleased(m_ID, getValue());
	}
}

//TODO ATTACH DETACH IN VATERKLASSE

void Slider::Attach(ISliderFunction* pCallback)
{
	//TODO no double attachments
	m_attachedFunctions.push_back(pCallback);
}

bool Slider::Detach(ISliderFunction* pCallback)
{
	for(unsigned int i = 0; i < m_attachedFunctions.size(); i++)
		if(m_attachedFunctions[i] == pCallback)
		{
			m_attachedFunctions.erase(m_attachedFunctions.begin() + i);
			return true;
		}
	return false;
}

bool Slider::isHit(sf::Vector2i & mouse)
{
	//check if mouse is on slider
	

	if( m_pBar[3].s.getPosition().x < mouse.x && m_pBar[3].s.getPosition().x + m_pBar[3].s.getSize().x > mouse.x &&
		m_pBar[3].s.getPosition().y < mouse.y && m_pBar[3].s.getPosition().y + m_pBar[3].s.getSize().y > mouse.y)
	{
		m_mouseOver = true;
		
	}
	else if(!m_mouseDown)
	{
		m_mouseOver = false;
	}
	//move slider

	if(m_mouseDown && m_mouseOver)
	{
		double oldValue = getValue();
		m_wasClicked = true;
		if(m_horizontal)
		{
			float delta = mouse.x - m_oldMouse.x;
			//std::cout << "Slider Mouse Delta :  x  " << delta << std::endl;
			m_pBar[3].s.setPosition(m_pBar[3].s.getPosition().x + delta , m_pBar[3].s.getPosition().y); 

			// restrict movement
			//x+
			if(m_pBar[3].s.getPosition().x > m_dimensions.width + m_dimensions.left - SLIDERENDBLOCKWIDTH * 2 - m_dimensions.height)
				m_pBar[3].s.setPosition(m_dimensions.width + m_dimensions.left - SLIDERENDBLOCKWIDTH * 2 - m_dimensions.height ,m_pBar[3].s.getPosition().y);
			//x-
			if(m_pBar[3].s.getPosition().x < m_dimensions.left + SLIDERENDBLOCKWIDTH)
				m_pBar[3].s.setPosition( m_dimensions.left + SLIDERENDBLOCKWIDTH ,m_pBar[3].s.getPosition().y);
		}
		else
		{
			float delta = mouse.y - m_oldMouse.y;
			//std::cout << "Slider Mouse Delta :  y  " << delta << std::endl;
			m_pBar[3].s.setPosition(m_pBar[3].s.getPosition().x, m_pBar[3].s.getPosition().y + delta);

			// restrict movement
			//y+
			if(m_pBar[3].s.getPosition().y > m_dimensions.height + m_dimensions.top - SLIDERENDBLOCKWIDTH * 2 - m_dimensions.width)
				m_pBar[3].s.setPosition(m_pBar[3].s.getPosition().x, m_dimensions.height + m_dimensions.top - SLIDERENDBLOCKWIDTH * 2 - m_dimensions.width);
			//y-
			if(m_pBar[3].s.getPosition().y < m_dimensions.top + SLIDERENDBLOCKWIDTH)
				m_pBar[3].s.setPosition(m_pBar[3].s.getPosition().x, m_dimensions.top + SLIDERENDBLOCKWIDTH );
		}

		if(oldValue != getValue())
			Notify();
	}
	
	m_oldMouse = mouse;
	return m_mouseOver;
}

void Slider::PressedRight(){}
void Slider::ReleasedRight(){}

void Slider::PressedLeft()
{
	if(m_mouseOver)
		m_mouseDown = true;
	
		

	//TODO notify
}

void Slider::ReleasedLeft()
{
	//TODO notify
	m_mouseDown = false;
	if(m_wasClicked)
	{
		Notify();
		m_wasClicked = false;
	}
}

void Slider::draw(RenderWindow* rw)
{
	for(int i = 0; i < 4; i++)
		rw->draw(m_pBar[i].s);
}
