#include "Statusbar.h"

//Ctro & Dtor-------------------------------------------------------
Statusbar::Statusbar(Vector2f pos, Vector2f size, StatusBarFunctions* OpenMenu)
{
	m_pOpenMenu = OpenMenu;

	m_BaseRect.setPosition(pos);
	m_BaseRect.setSize(size);
	m_BaseRect.setFillColor(MyColors.MenuBackground);

	m_BMenu = new StandardButton(Vector2f(pos.x + AbstandX, pos.y + 5), Vector2f(50, size.y-10),"Menü" , 1, true, false);
	m_BMenu->Attach(this); 
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
	return m_BMenu->MouseMoved(mouse);
}

bool Statusbar::PressedLeft()
{
	return m_BMenu->PressedLeft();
}

bool Statusbar::ReleasedLeft(){ return false; }
bool Statusbar::PressedRight(){ return false; }
bool Statusbar::ReleasedRight(){ return false; }

void Statusbar::animationTick() // IAnimation
{
	m_BMenu->animationTick();
}

void Statusbar::draw(sf::RenderWindow* rw) // IDrawable
{
	rw->draw(m_BaseRect);
	m_BMenu->draw(rw);

	for(int i = 0; i < m_TextboxContainer.size(); i++)
		m_TextboxContainer[i].draw(rw);
}

void Statusbar::onButtonClick(int id)
{
	switch(id)
	{
	case 1: 
			m_pOpenMenu->OpenMenu();
			break;

	default: break;
	}
}
