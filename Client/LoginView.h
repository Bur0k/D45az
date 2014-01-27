#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <SFML\Graphics.hpp>
#include <string>

#include "IView.h"
#include "StandardButton.h"
#include "Textbox.h"
#include "Textblock.h"
#include "Login.h"
#include "PlayerData.h"
#include "Connect.h"
#include "Background.h"

class LoginView : public IView , public IButtonfunction, public ITextBoxFunction
{
public:
	LoginView(Vector2u & size);
	~LoginView();

private:
	Views next;

	DrawVect m_DrawV;
	AnimateVect m_AnimateV;
	ClickVect m_ClickV;
	KeyInputVect m_KeyV;

	Textblock* logintext;
	Textblock* status;
	TextBox* name;
	Button* lgoinbutton;
	Background bg;

	void centering(Vector2u & size);

	Login* NL;
	Connect* connect;
	bool connected;
	Client* c;
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
	virtual void pt1zyklisch(double elapsedMs);

	virtual Views getType();

	void onTextBoxSend(int ID, std::string s);
};


#endif //LOGINVIEW_H