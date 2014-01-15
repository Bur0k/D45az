#include "Textbox.h"

TextBox::TextBox(float width, sf::String startText, Vector2f pos, bool sendOnReturn, int id)
{
	m_inFocus = false;
	m_returnIsSend = sendOnReturn;
	m_mouseOver = false;
	m_isStartStringDisplayed = true;
	m_cursorRight = false;

	m_ID = id;
	m_cursorPosition = 0;
	m_CharacterDisplayOffset = 0;
	m_anmation = 0;
	m_cursorAnimation = 0;

	Image img;
	if(!img.loadFromFile("Data/Images/Button.png"))
		std::cout << "textbox: Load Image Failed!" << std::endl;
	
	//select tiles from button tilesheet
	
	m_pBorder[0].t.loadFromImage(img, IntRect(0, 0, TEXTBOXBORDERSPACING, TEXTBOXBORDERSPACING));
	m_pBorder[1].t.loadFromImage(img, IntRect(TEXTBOXBORDERSPACING, 0, TEXTBOXBORDERSPACING, TEXTBOXBORDERSPACING));
	m_pBorder[2].t.loadFromImage(img, IntRect(TEXTBOXBORDERSPACING * 2, 0, TEXTBOXBORDERSPACING, TEXTBOXBORDERSPACING));
	m_pBorder[3].t.loadFromImage(img, IntRect(0, TEXTBOXBORDERSPACING, TEXTBOXBORDERSPACING, TEXTBOXBORDERSPACING));
	m_pBorder[4].t.loadFromImage(img, IntRect(TEXTBOXBORDERSPACING * 2, TEXTBOXBORDERSPACING, TEXTBOXBORDERSPACING, TEXTBOXBORDERSPACING));
	m_pBorder[5].t.loadFromImage(img, IntRect(0, TEXTBOXBORDERSPACING * 2, TEXTBOXBORDERSPACING, TEXTBOXBORDERSPACING));
	m_pBorder[6].t.loadFromImage(img, IntRect(TEXTBOXBORDERSPACING, TEXTBOXBORDERSPACING * 2, TEXTBOXBORDERSPACING, TEXTBOXBORDERSPACING));
	m_pBorder[7].t.loadFromImage(img, IntRect(TEXTBOXBORDERSPACING * 2, TEXTBOXBORDERSPACING * 2, TEXTBOXBORDERSPACING * 2, TEXTBOXBORDERSPACING));

	

	m_BaseRect.setPosition(pos.x + TEXTBOXBORDERSPACING / 2, pos.y + TEXTBOXBORDERSPACING / 2);
	m_BaseRect.setSize(Vector2f(width - TEXTBOXBORDERSPACING, TEXTBOXHEIGHT - TEXTBOXBORDERSPACING));
	m_BaseRect.setFillColor(m_nofocusCol);

	m_displayedText.setFont(MyFonts::getFont(GameFonts::ARIAL));
	m_displayedText.setString(startText);
	m_displayedText.setPosition(m_BaseRect.getPosition());
	m_displayedText.move(TEXTBOXBORDERSPACING, TEXTBOXBORDERSPACING / 3);
	m_displayedText.setCharacterSize(25);

	m_dimensions.top = pos.y;
	m_dimensions.left = pos.x;
	m_dimensions.width = width;
	m_dimensions.height = TEXTBOXHEIGHT;
	
	m_cursor.setPosition(m_dimensions.left + TEXTBOXBORDERSPACING, m_dimensions.top + TEXTBOXBORDERSPACING);
	m_cursor.setSize(Vector2f(TEXTBOXCURSORWIDTH, TEXTBOXHEIGHT - TEXTBOXBORDERSPACING * 2));

	m_focusCol = MyColors.DarkGray;
	m_nofocusCol = MyColors.Gray;

}

TextBox::~TextBox()
{
	m_attachedFunctions.clear();
}

void TextBox::onKeyDown(sf::Event e)
{
	if(!m_inFocus)
		return;

	switch(e.key.code)
	{
	case Keyboard::BackSpace:
		if(m_text.size() > 0 && m_cursorPosition + m_CharacterDisplayOffset > 0)
		{
			m_text.erase(m_text.begin() + m_cursorPosition + m_CharacterDisplayOffset - 1);
			moveCursor(true);
		}
		break;

	case Keyboard::Delete:
		if(m_text.size() > 0 && m_cursorPosition + m_CharacterDisplayOffset != m_text.size())
		{
			m_text.erase(m_text.begin() + m_cursorPosition + m_CharacterDisplayOffset);
			fitText();
		}
		break;

	case Keyboard::Left:
		moveCursor(true);
		break;

	case Keyboard::Right:
		moveCursor(false);
		break;

	case Keyboard::Return:
		if(m_returnIsSend)
			Notify();
		break;
	}
}

void TextBox::onKeyUp(sf::Event){}

void TextBox::moveCursor(bool left)
{
	if(left)
	{
		if(m_cursorPosition + m_CharacterDisplayOffset >= 0)
		{
			if(m_cursorPosition == 0)
			{
				m_CharacterDisplayOffset -= (m_CharacterDisplayOffset > 0)? 1 : 0;
			}
			else
				m_cursorPosition--;
		}
	}
	else //right
	{
		if(m_cursorPosition + m_CharacterDisplayOffset < m_text.size())
		{
			//if cursor would be off to the right dont move cursor at all instead offset the string
			if(m_cursorRight)
			{
				m_CharacterDisplayOffset++;
			}
			else
				m_cursorPosition++;
		}
	}
	m_cursorAnimation = 0;
	fitText();
}

void TextBox::onTextInput(std::string s)
{
	if(m_inFocus)
	{
		m_text.insert(m_cursorPosition + m_CharacterDisplayOffset,s);
		moveCursor(false);
	}
}

void TextBox::fitText()
{
	std::string cut = m_text.substr(m_CharacterDisplayOffset, m_text.size() -  m_CharacterDisplayOffset);
	std::cout << m_text << std::endl << cut << std::endl;
	Rect<float> textDimensions;
	textDimensions.width = 0;
	
	std::string dispStr;
	int index = 0;
	bool cursorLast = false;
	m_cursorRight = false;
	while(index < cut.size()) 
	{
		dispStr.append(cut.substr(index, 1));
		index++;

		m_displayedText.setString(dispStr);
		textDimensions = m_displayedText.getLocalBounds();
	
		if(index == m_cursorPosition)
		{
			m_cursor.setPosition(m_displayedText.getPosition().x + textDimensions.width, m_cursor.getPosition().y);
			cursorLast = true;
		}
		else
			cursorLast = false;

		if(textDimensions.width >= m_BaseRect.getSize().x - TEXTBOXBORDERSPACING * 3.5) //stop if we run out of space
		{
			m_cursorRight = cursorLast;
			break;
		}
	}
	std::cout << "cursor position : " << m_cursorPosition << " string offset : " << m_CharacterDisplayOffset << std::endl;
	if(m_cursorPosition == 0)
		m_cursor.setPosition(m_displayedText.getPosition().x, m_cursor.getPosition().y);
	if(m_text.size() == 0)
		m_displayedText.setString("");
	if(index < m_cursorPosition)
	{
		m_CharacterDisplayOffset++;
		m_cursorPosition--;
		fitText();
	}
}

bool TextBox::isHit(sf::Vector2i & mouse)
{
	if( mouse.x >= m_dimensions.left && mouse.x <= m_dimensions.left + m_dimensions.width &&
		mouse.y >= m_dimensions.top && mouse.y <= m_dimensions.top + m_dimensions.height)
		m_mouseOver = true;
	else
		m_mouseOver = false;

	return m_mouseOver;
}

bool TextBox::PressedLeft()
{
	if(m_mouseOver && !m_inFocus)
	{
		m_inFocus = true;
		m_cursorAnimation = 0;
		if(m_isStartStringDisplayed)
		{
			m_isStartStringDisplayed = false;
			fitText();
		}
		return true;
	}
	else if(m_inFocus && m_mouseOver)
		return true;
	//TODO set cursor with mouse
	else if(!m_mouseOver)
		m_inFocus = false;

	return false;
}

bool TextBox::ReleasedLeft(){ return false; }
bool TextBox::PressedRight(){ return false; }
bool TextBox::ReleasedRight(){ return false; }

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

void TextBox::clear()
{
	m_cursorPosition = 0;
	m_text.clear();
	fitText();
	m_cursorRight = false;
}

std::ostream& TextBox::operator<<(std::ostream& os)
{
	os << m_text;
    return os;
}

void TextBox::animationTick()
{
	//cursor blinking
	if(m_inFocus)
	{
		m_cursorAnimation++;
		if(m_cursorAnimation > TEXTBOXCURSORBLINKTIME * 2)
			m_cursorAnimation = 0;

		if(m_cursorAnimation <= TEXTBOXCURSORBLINKTIME)
		{
			m_cursor.setFillColor(MyColors.White);
		}
		else
		{
			m_cursor.setFillColor(MyColors.Transparent);
		}
	}

	//animation for backgroundchange when getting into and out of focus
	if(m_anmation < TEXTBOXANIMATIONLENGTH && m_inFocus)
	{
		m_anmation++;
	}
	else if(m_anmation > 0 && !m_inFocus)
	{
		m_anmation--;
	}
	else
		return;	//if m_animation hasnt changed

	

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

	for(int i = 0; i < 8; i++)
		rw->draw(m_pBorder[i].s);

	//TODO draw nice graphics around m_BaseRect
}
