#ifndef SPLITTEDSPRITE_H
#define SPLITTEDSPRITE_H

#include <SFML\Graphics.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <math.h>

class SplittedSprite : public sf::Sprite
{
protected:
	sf::Vector2i frameSize;
	int framesPerRow;
	int currentFrame;

public:
	SplittedSprite(sf::Texture* Texture,int FrameWidth,int FrameHeight);
	void setFrame(int frame);
	sf::Vector2i getFrameSize();
	int getFramesPerRow();
	int getFrame();
};

#endif