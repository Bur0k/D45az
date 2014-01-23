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

	//m_TBGold = new Textblock(Vector2f(200,5), Vector2f(100, 100), String("1038"), 40);

	preload_Textures(); // texturen laden

	for(int i = 0; i < m_vTextures.size(); i++)
	{
		Sprite Stp;
		Stp.setTexture(m_vTextures[i]);
		Stp.setPosition(100 + IconX * i, IconY);
		m_vSPictures.push_back(Stp);
	}

}


Statusbar::~Statusbar(void)
{
	//Elemente
	delete m_BMenu;
}

void Statusbar::preload_Textures()
{
	Texture tmp_texture;
	String Ablageort = "Data/Images/";

	m_vTexturenames.push_back(Ablageort + "armee.png"); //Iconnamen manuell einfügen
	m_vTexturenames.push_back(Ablageort + "gold.png");
	m_vTexturenames.push_back(Ablageort + "stadt.png");
	m_vTexturenames.push_back(Ablageort + "runden_1.png");

	for(int i = 0; i < m_vTexturenames.size(); i++)
	{
		tmp_texture.loadFromFile(m_vTexturenames[i]);
		m_vTextures.push_back(tmp_texture);
	}
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

	for(int i = 0; i < m_vSPictures.size(); i++)
		rw->draw(m_vSPictures[i]);

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
