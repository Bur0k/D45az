#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>

#include "IClickable.h"
#include "IKeyboardInput.h"
#include "graphic_globals.h"
#include "IDrawable.h"
#include "IAnimatable.h"

using namespace sf;

class ITextBoxFunction
{
public:
	virtual void onTextBoxSend(int ID, std::string s)=0;
};

typedef std::vector<ITextBoxFunction*>TextBoxFuncVect;


#define TEXTBOXHEIGHT 50
#define TEXTBOXBORDERSPACING 10
#define TEXTBOXCURSORWIDTH 3
#define TEXTBOXANIMATIONLENGTH 30
#define TEXTBOXCURSORBLINKTIME 15 


class TextBox : public IKeyboardinput, public IClickable, public IDrawable, public IAnimatable
{
protected:
	bool m_inFocus; 
	bool m_returnIsSend;
	bool m_mouseOver;
	bool m_isStartStringDisplayed;
	bool m_cursorRight;

	SpriteTex* m_pBorder;

	/* Sprite Layout
		0 1 2
		3 - 4
		5 6 7
	*/

	int m_ID;
	//cursor position on screen
	int m_cursorPosition;
	//amount of chars that the string is offset to the left (or amount of chars NOT displayed in the box)
	int m_CharacterDisplayOffset;
	int m_anmation;
	int m_cursorAnimation;

	Color m_focusCol;
	Color m_nofocusCol;

	//used as reference object for other graphic elements
	Rect<float> m_dimensions;
	RectangleShape m_BaseRect;

	//will only be drawn if in focus
	RectangleShape m_cursor;

	std::string m_text;
	Text m_displayedText;
	TextBoxFuncVect m_attachedFunctions;
	
	//decides which part of m_text will be displayed
	void fitText();
	void moveCursor(bool left);
	void positionBorderElements();
	
public:
	
	///@param startText should be description of what the box does or an example of expected format
	TextBox(float width, sf::String startText, Vector2f pos, bool sendOnReturn, int id);
	~TextBox();

	std::ostream& operator<<(std::ostream&);

	void Notify();
	void Attach(ITextBoxFunction*);
	bool Detach(ITextBoxFunction*);

	void move(Vector2f);
	Vector2f getPos();
	void setPos(Vector2f);

	Vector2f getSize();
	void setSize(float width);

	std::string getText();
	void setText(std::string);
	void clear();


	//implementing Ikeyboardinput
	virtual void onKeyDown(sf::Event);
	virtual void onKeyUp(sf::Event);
	virtual void onTextInput(std::string s);

	//implemnting Iclickable
	virtual bool MouseMoved(sf::Vector2i &);
	virtual bool PressedRight();
	virtual bool PressedLeft();
	virtual bool ReleasedRight();
	virtual bool ReleasedLeft();

	//implementing IDrawable
	virtual void draw(sf::RenderWindow* rw);

	//implementing IAnimatable
	virtual void animationTick();
};


#endif //TEXTBOX_H