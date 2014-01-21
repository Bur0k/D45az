#include "CommitButton.h"


CommitButton::CommitButton(Vector2f pos, Vector2f size, sf::String S, int ID, bool lock, Vector2u winSize, unsigned int characterSize) :  Button(pos, size, S, ID, lock, characterSize)
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
	foreground.s.setPosition(this->getPosition().x - 50, this->getPosition().y - 50);
	foreground.s.setSize((sf::Vector2f)image.getSize());

	std::cout << "width: " << windowSize.x << "x bild: " << this->getPosition().x - 50 << std::endl;
	std::cout << "height: " << windowSize.y << "y bild: " << this->getPosition().y - 50 << std::endl;
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

void CommitButton::onResize(Vector2u winSize)
{
	this->windowSize = winSize;
	this->setPosition(windowSize.x - this->getSize().x, windowSize.y - this->getSize().y);
	foreground.s.setPosition(this->getPosition().x - 50, this->getPosition().y - 50);
	

	std::cout << "width: " << windowSize.x << "x bild: " << foreground.s.getPosition().x << "  x button: " << this->getPosition().x <<std::endl;
	std::cout << "height: " << windowSize.y << "y bild: " << foreground.s.getPosition().y << "  y button: " << this->getPosition().y << std::endl;
}
