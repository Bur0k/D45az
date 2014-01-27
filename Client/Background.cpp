#include "Background.h"

Background::Background()
{
	Texture image;
	if(!image.loadFromFile("Data/Images/background.png"))
		std::cout << "LoginView.cpp:  couldn't load background.png" << std::endl;

	bgimage.t = image;
	bgimage.s.setTexture(& bgimage.t);                      
	bgimage.s.setPosition(0,0);
	bgimage.s.setSize((sf::Vector2f)image.getSize());
}

Background::Background(std::string path)
{
	Texture image;
	if(!image.loadFromFile(path))
		std::cout << "LoginView.cpp:  couldn't load " << path << std::endl;

	bgimage.t = image;
	bgimage.s.setTexture(& bgimage.t);                      
	bgimage.s.setPosition(0,0);
	bgimage.s.setSize((sf::Vector2f)image.getSize());
}

Background::~Background()
{

}

//IDrawable
void Background::draw(sf::RenderWindow* rw)
{
	rw->draw(bgimage.s);
}

void Background::onResize(sf::Vector2u & size)
{
	bgimage.s.setPosition(size.x / 2 - bgimage.s.getSize().x / 2,
						  size.y / 2 - bgimage.s.getSize().y / 2);
}

