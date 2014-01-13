#include "Textbox.h"

TextBox::TextBox(float width, sf::String startText, Vector2f pos, bool sendOnReturn, int id)
{
	m_inFocus = false;
	m_returnIsSend = sendOnReturn;
	m_mouseOver = false;
	m_isStartStringDisplayed = true;

	m_ID = id;
	m_cursorPosition = 0;
	m_CharacterDisplayOffset = 0;
	m_anmation = 0;

	m_displayedText.setFont(MyFonts::getFont(GameFonts::ARIAL));
	m_displayedText.setString(startText);


	m_BaseRect.setPosition(pos.x + TEXTBOXBORDERSPACING / 2, pos.y + TEXTBOXBORDERSPACING / 2);
	m_BaseRect.setSize(Vector2f(width - TEXTBOXBORDERSPACING, TEXTBOXHEIGHT - TEXTBOXBORDERSPACING));

	m_dimensions.top = pos.y;
	m_dimensions.left = pos.x;
	m_dimensions.width = width;
	
	m_cursor.setPosition(m_dimensions.left + TEXTBOXBORDERSPACING, m_dimensions.top + TEXTBOXBORDERSPACING);
	m_cursor.setSize(Vector2f(TEXTBOXCURSORWIDTH, TEXTBOXHEIGHT - TEXTBOXBORDERSPACING * 2));

	m_focusCol = MyColors.DarkGray;
	m_nofocusCol = MyColors.Gray;

}


void TextBox::onKeyDown(sf::Event e)
{
	switch(e.key.code)
	{
	case Keyboard::BackSpace:
		if(m_text.size() > 1 && m_cursorPosition > 0)
		{
			m_text.erase(m_text.begin() + m_cursorPosition - 1);
			m_cursorPosition--;
			fitText();
		}
		break;

	case Keyboard::Left:
		if(m_cursorPosition > 0)
		{
			m_cursorPosition--;
			fitText();
		}
		break;
	case Keyboard::Right:
		if((unsigned)m_cursorPosition < m_text.size())
		{
			m_cursorPosition++;
			fitText();
		}
		break;
	}
}
void TextBox::onKeyUp(sf::Event){}

void TextBox::onTextInput(std::string s)
{
	m_text.insert(m_cursorPosition,s);
	m_cursorPosition++;
	fitText();
	
}

void TextBox::fitText()
{
	//TODO 
	//if neccessary substring of m_text for m_displayedtext
	//update curosor position on screen
}

bool TextBox::isHit(sf::Vector2i &)
{
	Vector2i mouse = Mouse::getPosition();
	if( mouse.x >= m_dimensions.left && mouse.x <= m_dimensions.left + m_dimensions.width &&
		mouse.y >= m_dimensions.top && mouse.y <= m_dimensions.top + m_dimensions.height)
		m_mouseOver = true;
	else
		m_mouseOver = false;

	return m_mouseOver;
}

void TextBox::PressedLeft()
{
	if(m_mouseOver)
	{
		m_inFocus = true;
		if(m_isStartStringDisplayed)
		{
			m_displayedText.setString(m_text);
			m_isStartStringDisplayed = false;
		}
	}
	else
		m_inFocus = false;
}

void TextBox::ReleasedLeft(){}
void TextBox::PressedRight(){}
void TextBox::ReleasedRight(){}

void TextBox::Notify()
{
	for(unsigned int i = 0; i < m_attachedFunctions.size(); i++)
	{
		m_attachedFunctions[i]->onTextBoxSend(m_ID, m_text);
	}
}

void TextBox::attach(ITextBoxFunction* pCallback)
{
	//TODO no double attachments
	m_attachedFunctions.push_back(pCallback);
}

bool TextBox::detach(ITextBoxFunction* pCallback)
{
	for(unsigned int i = 0; i < m_attachedFunctions.size(); i++)
		if(m_attachedFunctions[i] == pCallback)
		{
			m_attachedFunctions.erase(m_attachedFunctions.begin() + i);
			return true;
		}
	return false;
}

void TextBox::move(Vector2f delta)
{
	m_dimensions.left += delta.x;
	m_dimensions.top += delta.y;
	
	m_BaseRect.move(delta);
	m_cursor.move(delta);
	m_displayedText.move(delta);
}

Vector2f TextBox::getPos()
{
	return Vector2f(m_dimensions.left, m_dimensions.top);
}

void TextBox::setPos(Vector2f){}

Vector2f TextBox::getSize()
{
	return Vector2f(m_dimensions.width, m_dimensions.height);
}

void TextBox::setSize(float width){}

std::string TextBox::getText()
{
	return m_text;
}

void  TextBox::setText(std::string){}

std::ostream& TextBox::operator<<(std::ostream& os)
{
	os << (std::string)m_text;
    return os;
}

void TextBox::animationTick()
{
	if(m_anmation < TEXTBOXANIMATIONLENGTH && m_inFocus)
	{
		m_anmation++;
	}
	else if(m_anmation > 0 && !m_inFocus)
	{
		m_anmation--;
	}
	else
		return;	//if m_animation hasnt changed return here

	double ratio1 =  sqrt((double)m_anmation) / sqrt((double)TEXTBOXANIMATIONLENGTH);
	double ratio2 = 1 - ratio1;
	m_BaseRect.setFillColor(Color(  (Uint8)(m_nofocusCol.r * ratio1 + m_focusCol.r * ratio2),
									(Uint8)(m_nofocusCol.g * ratio1 + m_focusCol.g * ratio2),
									(Uint8)(m_nofocusCol.b * ratio1 + m_focusCol.b * ratio2),
									(Uint8)(m_nofocusCol.a * ratio1 + m_focusCol.a * ratio2)));
}

void TextBox::draw(sf::RenderWindow* rw)
{
	rw->draw(m_BaseRect);
	rw->draw(m_displayedText);
	if(m_inFocus) 
		rw->draw(m_cursor);

	//TODO draw nice graphics around m_BaseRect
}
