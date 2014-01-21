#ifndef COMMITBUTTON_H
#define COMMITBUTTON_H

#include "Button.h"

class CommitButton : public Button
{
private:
	Vector2u windowSize;
	SpriteTex foreground;

public:
	CommitButton(Vector2f pos, Vector2f size, sf::String S, int ID, bool lock, Vector2u winSize);
	~CommitButton();

	virtual void draw(RenderWindow* rw);
	void onResize(Vector2u winSize);

};



#endif 
