#include "Statusbar.h"

//Ctro & Dtor-------------------------------------------------------
Statusbar::Statusbar(Vector2f pos, Vector2f size)
{
	m_BaseRect.setPosition(pos);
	m_BaseRect.setSize(size);
	m_BaseRect.setFillColor(MyColors.Gray);

	m_BMenu = new StandardButton(Vector2f(pos.x + AbstandX, pos.y + 5), Vector2f(50, size.y-10),"Menü" , 1, true);
	m_BMenu->setFillColor(MyColors.Red);
}


Statusbar::~Statusbar(void)
{
	delete m_BMenu;
}

//Getter & Setter-------------------------------------------------------
Vector2f Statusbar::getPosition()
{
	return m_BaseRect.getPosition();
}

void Statusbar::setPosition(Vector2f pos)
{
	m_BaseRect.setPosition(pos);
}

void Statusbar::setBgColor(Color c)
{
	m_BaseRect.setFillColor(c);
}

void Statusbar::Resize(Vector2f new_size)
{
		//SBar->Resize(Vector2f(m_size.x, Statusbarheight)); // Statusbar anpassen
	m_BaseRect.setSize(new_size);
}

//Hilfsfunktionen-------------------------------------------------------




//Interface-Funktionen-------------------------------------------------------
bool Statusbar::MouseMoved(sf::Vector2i & mouse)
{
	//checken ob maus nach einer bewegung auf der statusbar ist
	if( mouse.x >= m_BaseRect.getPosition().x && mouse.x <= m_BaseRect.getPosition().x + m_BaseRect.getSize().x &&
		mouse.y >= m_BaseRect.getPosition().y && mouse.y <= m_BaseRect.getPosition().y + m_BaseRect.getSize().y)
		m_mouseOver = true;
	else
		m_mouseOver = false;

	return m_mouseOver;
}

bool Statusbar::PressedLeft()
{
	if(m_mouseOver && !m_inFocus) //TODO verschiedene objekte müssen anwählbar sein
	{
		m_inFocus = true;
	}
	else if(m_inFocus && m_mouseOver)
		return true;
	else if(!m_mouseOver)
		m_inFocus = false;

	return false;
}

bool Statusbar::ReleasedLeft(){ return false; }
bool Statusbar::PressedRight(){ return false; }
bool Statusbar::ReleasedRight(){ return false; }

void Statusbar::animationTick() // IAnimation
{
}

void Statusbar::draw(sf::RenderWindow* rw) // IDrawable
{
	rw->draw(m_BaseRect);
	m_BMenu->draw(rw);

	for(int i = 0; i < m_TextboxContainer.size(); i++)
		m_TextboxContainer[i].draw(rw);
}
