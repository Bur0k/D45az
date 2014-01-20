#include "CommitButton.h"


CommitButton::CommitButton(Vector2u winSize)
{
	this->windowSize = winSize;

	Texture image;
	//150, 150 --- 100, 100
	if(!image.loadFromFile("Data/Images/commit-Button.png"))
	{
		std::cout << "commit-Button couldn't load" << std::endl;
	}
	else
	{
		std::cout << "commit-Button has loaded" << std::endl;                                                           //Startbild laden
	}
	foreground.t = image;
	foreground.s.setTexture(&foreground.t);                      
	foreground.s.setPosition(50,50);
	foreground.s.setSize((sf::Vector2f)image.getSize());
}


CommitButton::~CommitButton()
{

}

void CommitButton::draw(RenderWindow* rw)
{
	rw->draw(*this);
	rw->draw(foreground.s);
	rw->draw(m_buttonText);
}

void CommitButton::onResize()
{
	this->setPosition(windowSize.x - 150, windowSize.y - 150);
}
