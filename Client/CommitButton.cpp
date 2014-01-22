#include "CommitButton.h"


CommitButton::CommitButton(Vector2f pos, Vector2f size, sf::String S, int ID, bool lock, Vector2u winSize, unsigned int characterSize) :
	Button(Vector2f(winSize.x - 100, winSize.y - 100), Vector2f(100,100), S, ID, lock, characterSize)
{
	this->windowSize = winSize;

	Texture image;
	if(!image.loadFromFile("Data/Images/commit-Button.png"))
	{
		std::cout << "commit-Button couldn't load" << std::endl;
	}

	foreground.t = image;
	foreground.s.setTexture(&foreground.t);                      
	foreground.s.setPosition(this->getPosition().x - 50, this->getPosition().y - 50);
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

void CommitButton::onResize(Vector2u winSize)
{
	this->windowSize = winSize;
	this->setPosition(windowSize.x - this->getSize().x, windowSize.y - this->getSize().y);
	this->fitText(10);
	foreground.s.setPosition(this->getPosition().x - 50, this->getPosition().y - 50);
	
}
