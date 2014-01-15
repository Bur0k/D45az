#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include "IView.h"

class LoginView : public IView , public IButtonfunction, public ITextBoxFunction
{
public:
	LoginView();
	~LoginView();

	DrawVect DrawV;
	AnimateVect AnimateV;
	ClickVect ClickV;
	KeyInputVect KeyV;



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