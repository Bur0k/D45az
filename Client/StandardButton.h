#ifndef STANDARDBUTTON_H
#define STANDARDBUTTON_H

#include <SFML\Graphics.hpp>
#include "Button.h"
using namespace sf;

//go-to-button if you don't need any special features
class StandardButton : public Button
{
public:
	StandardButton();
	///@param Size x or y should be bigger than 10 px
	StandardButton(Vector2f pos,Vector2f Size, String S);
	~StandardButton();

	void draw();
};


#endif