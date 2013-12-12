#include "SplittedSprite.h"

SplittedSprite::SplittedSprite(sf::Texture* Texture,int FrameWidth,int FrameHeight):sf::Sprite(*Texture)
{
	frameSize.x= FrameWidth;
	frameSize.y= FrameHeight;

	framesPerRow = (int)(std::ceil((double)(Texture->getSize().x / frameSize.x)));

	setFrame(0);
}

void SplittedSprite::setFrame(int frame)
{
	currentFrame=frame;
	int left = (frame % framesPerRow) * frameSize.x;
	int top = (frame / framesPerRow) *  frameSize.x;
	
	setTextureRect(sf::IntRect(left, top , frameSize.x, frameSize.y));
}

sf::Vector2i SplittedSprite::getFrameSize()
{
	return frameSize;
}

int SplittedSprite::getFramesPerRow()
{
	return framesPerRow;
}

int SplittedSprite::getFrame()
{
	return currentFrame;
}