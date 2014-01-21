#include "Statusbar.h"

//Ctro & Dtor-------------------------------------------------------
Statusbar::Statusbar(Vector2f pos, Vector2f size)
{
	m_BaseRect.setPosition(pos);
	m_BaseRect.setSize(size);
	m_BaseRect.setFillColor(MyColors.MenuBackground);

	m_BMenu = new StandardButton(Vector2f(pos.x + AbstandX, pos.y + 5), Vector2f(50, size.y-10),"Menü" , 1, true, false);
	m_BMenu->setFillColor(MyColors.Red);
}


Statusbar::~Statusbar(void)
{
	delete m_BMenu;
}

//Getter & Setter-------------------------------------------------------
void Statusbar::setMouse(Vector2f pos)
{
	m_MousePos = pos;
}

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
	m_BaseRect.setSize(new_size);
}

//Hilfsfunktionen-------------------------------------------------------




//Interface-Funktionen-------------------------------------------------------
bool Statusbar::MouseMoved(sf::Vector2i & mouse)
{
	//checken ob maus nach einer bewegung auf der statusbar ist
	if( mouse.x >= m_BaseRect.getPosition().x && mouse.x <= m_BaseRect.getPosition().x + m_BaseRect.getSize().x &&
		mouse.y >= m_BaseRect.getPosition().y && mouse.y <= m_BaseRect.getPosition().y + m_BaseRect.getSize().y)
	{
		setMouse(Vector2f(mouse.x, mouse.y));	
		m_mouseOver = true;
	}
	else
		m_mouseOver = false;

	return m_mouseOver;
}

bool Statusbar::PressedLeft()
{
	if(m_mouseOver) //TODO verschiedene objekte müssen anwählbar sein
	{
		if(m_MousePos.x >= m_BMenu->getPosition().x && m_MousePos.x <= m_BMenu->getOrigin().x + m_BMenu->getPosition().x
			&& m_MousePos.y >= m_BMenu->getPosition().y && m_MousePos.y <= m_BMenu->getOrigin().y + m_BMenu->getPosition().y)
		{
//			m_pGame->LoadView(Views::MENU);
	//		m_pGame->setMenubottun(1); // MEnü an
		}
		return true;
	}
	else 
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
