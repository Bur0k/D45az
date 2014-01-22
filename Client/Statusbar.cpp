#include "Statusbar.h"

//Ctro & Dtor-------------------------------------------------------
Statusbar::Statusbar(Vector2f pos, Vector2f size, StatusBarFunctions* OpenMenu)
{
	m_pOpenMenu = OpenMenu;

	m_BaseRect.setPosition(pos);
	m_BaseRect.setSize(size);
	m_BaseRect.setFillColor(MyColors.MenuBackground);

	//angezeigte Elemente
	m_BMenu = new StandardButton(Vector2f(pos.x + 5, pos.y + 5), Vector2f(50, size.y-10),"Menü" , 1, false, false);
	m_BMenu->Attach(this); 

	m_TBGold = new Textblock(Vector2f(200,5), Vector2f(100, 100), String("1038"), 40);

/*
	if(m_Ttmp.loadFromFile("Data/Images/gold.png"))
	{
		Sprite* Stmp = new Sprite(m_Ttmp);
		m_vSPictures.push_back(Stmp);
	}
	if(m_Ttmp.loadFromFile("Data/Images/gold.png"))
	{
		Sprite* Stmp = new Sprite(m_Ttmp);
		m_vSPictures.push_back(Stmp);
	}
	if(m_Ttmp.loadFromFile("Data/Images/gold.png"))
	{
		Sprite* Stmp = new Sprite(m_Ttmp);
		m_vSPictures.push_back(Stmp);
	}
	if(m_Ttmp.loadFromFile("Data/Images/gold.png"))
	{
		Sprite* Stmp = new Sprite(m_Ttmp);
		m_vSPictures.push_back(Stmp);
	}
	*/
}


Statusbar::~Statusbar(void)
{
	//Elemente
	delete m_BMenu;
	//delete m_SGold;
	delete m_TBGold;
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
	m_BaseRect.setSize(Vector2f(new_size.x, Statusbarheight));
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

bool Statusbar::ReleasedLeft()
{ 
	return m_BMenu->ReleasedLeft(); 
}
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
	m_TBGold->draw(rw);
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
