#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <SFML\Graphics.hpp>
#include <string>

#include "IView.h"
#include "StandardButton.h"
#include "Textbox.h"
#include "Textblock.h"

class LoginView : public IView , public IButtonfunction
{
public:
	LoginView(Vector2u & size);
	~LoginView();

private:
	DrawVect m_DrawV;
	AnimateVect m_AnimateV;
	ClickVect m_ClickV;
	KeyInputVect m_KeyV;

	Textblock* logintext;
	TextBox* name;
	Button* lgoinbutton;
	SpriteTex background;

	void centering(Vector2u & size);
	
public:
	virtual Views nextState();
	//implementing a lot of interfaces

	virtual void onButtonClick(int);

	virtual void draw(sf::RenderWindow* rw);

	virtual bool MouseMoved(sf::Vector2i &);
	virtual bool PressedRight();
	virtual bool PressedLeft();
	virtual bool ReleasedRight();
	virtual bool ReleasedLeft();
	
	virtual void animationTick(); 
	
	virtual void onKeyDown(sf::Event);
	virtual void onKeyUp(sf::Event);
	virtual void onTextInput(std::string s);

	virtual void onResize(sf::Vector2u &);
	virtual void update(double elpasedMs);

	virtual Views getType();
};


#endif //LOGINVIEW_H