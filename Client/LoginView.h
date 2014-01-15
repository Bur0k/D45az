#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <SFML\Graphics.hpp>

#include "IView.h"
#include "StandardButton.h"
#include "Textbox.h"
#include "Textblock.h"

class LoginView : public IView , public IButtonfunction, public ITextBoxFunction
{
public:
	LoginView();
	~LoginView();

	DrawVect m_DrawV;
	AnimateVect m_AnimateV;
	ClickVect m_ClickV;
	KeyInputVect m_KeyV;

	Textblock logintext;
	TextBox* name;
	Button* lgoinbutton;



	//implementing a lot of interfaces
	virtual void onTextBoxSend(int ID, std::string s);

	virtual void onButtonClick(int);

	virtual void draw(sf::RenderWindow* rw);

	virtual bool isHit(sf::Vector2i &);
	virtual bool PressedRight();
	virtual bool PressedLeft();
	virtual bool ReleasedRight();
	virtual bool ReleasedLeft();
	
	virtual void animationTick(); 
	
	virtual void onKeyDown(sf::Event);
	virtual void onKeyUp(sf::Event);
	virtual void onTextInput(std::string s);

};


#endif //LOGINVIEW_H