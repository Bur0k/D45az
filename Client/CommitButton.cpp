#include "CommitButton.h"


CommitButton::CommitButton(Vector2u winSize)
{
	this->windowSize = winSize;

	Texture image;
	//150, 150 --- 100, 100
	if(!image.loadFromFile("Data/Images/background.png"))
	{
		std::cout << "Texture couldn't load" << std::endl;
	}
	else
	{
		std::cout << "Texture has loaded" << std::endl;                                                           //Startbild laden
	}
	foreground.t = image;
	foreground.s.setTexture(&foreground.t);                      
	foreground.s.setPosition(0,0);
	foreground.s.setSize((sf::Vector2f)image.getSize());
}


CommitButton::~CommitButton()
{

}

void CommitButton::draw(RenderWindow* rw)
{
	rw->draw(*this);
	rw->draw(m_buttonText);
}
