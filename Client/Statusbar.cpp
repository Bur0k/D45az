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

	// Icons und LABELS erstellen
	preload_Textures(); // texturen laden
	for(int i = 0; i < m_vTextures.size(); i++)
	{
		Sprite Stp;
		Stp.setTexture(m_vTextures[i]);
		Stp.setPosition(IconOffset + IconX * i, IconY);
		m_vSPictures.push_back(Stp);

		Textblock* Tb = new Textblock(Vector2f(LabelOffset + IconX * i, IconY), Vector2f(100, 100), String("0000"), 40);
		Tb->setFillColor(MyColors.Transparent);
		Tb->setFontColor(MyColors.White);
		m_vTLabels.push_back(Tb);
	}

}


Statusbar::~Statusbar(void)
{
	//Elemente
	delete m_BMenu;
	for(int i = 0; i < m_vTLabels.size(); i ++)
		delete m_vTLabels[i];
}

void Statusbar::preload_Textures()
{
	Texture tmp_texture;
	String Ablageort = "Data/Images/";

	// Reihenfolge wie Enums 
	m_vTexturenames.push_back(Ablageort + "gold.png");
	m_vTexturenames.push_back(Ablageort + "armee.png"); //Iconnamen manuell einfügen
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

void Statusbar::setValue(enum Icons icon, int value)
{
	String tmp = to_string(value);
	Rect<float> textwidth = m_vTLabels[icon]->getLocalBounds();
	textwidth.width = 100;
	m_vTLabels[icon]->setText(tmp, Vector2f(100,100));
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
	setValue(Geld, 5);
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
	{
		rw->draw(m_vSPictures[i]);
		m_vTLabels[i]->draw(rw);
	}

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
