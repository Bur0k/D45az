#ifndef COMMITBUTTON_H
#define COMMITBUTTON_H

#include "Button.h"

class CommitButton : public Button
{
private:
	Vector2u windowSize;
	SpriteTex foreground;

public:
	CommitButton(Vector2u winSize);
	~CommitButton();

	void draw(RenderWindow* rw);
	void onResize();

};



#endif 
