#include "Textblock.h"

Textblock::Textblock()
{
	//TODO
}

Textblock::~Textblock()
{
	//TODO
}

Textblock::Textblock(Vector2f pos, Vector2f size, String S, int CharSize)
{
	setPosition(pos);
	m_Font = Font(MyFonts::getFont(GameFonts::ARIAL));
	m_textblockText.setFont(m_Font);
	m_textblockText.setPosition(getPosition());
	m_textblockText.setColor(MyColors.Black);
	m_textblockText.setCharacterSize(CharSize);
	m_textblockText.setString(lineBreak(S, size));
	textsize = m_textblockText.getLocalBounds();
	this->setSize(Vector2f(textsize.width + 5, textsize.height + 10));
	m_color = MyColors.Gray;
	setFillColor(m_color);
	fixCharsize();

	if(S.isEmpty)
	{
		textsize.height = 0;
		textsize.width = 0;
	}
}

Vector2f Textblock::getTBsize()
{
	return this->getSize();
}

void Textblock::setText(String text, Vector2f size)
{
	m_textblockText.setString(lineBreak(text, size));
	textsize = m_textblockText.getLocalBounds();
	this->setSize(Vector2f(textsize.width + 5, textsize.height + 10));
}

void Textblock::setPos(Vector2f pos)
{
	this->setPosition(pos);
	textsize = m_textblockText.getLocalBounds();
	this->setSize(Vector2f(textsize.width + 5, textsize.height + 10));
	m_textblockText.setPosition(pos);
	fixCharsize();
}

void Textblock::setFontColor(Color color)
{
	m_textblockText.setColor(color);
}

void Textblock::setBackgroundColor(Color color)
{
	this->setFillColor(color);
}

void Textblock::setCharSize(int CharSize)
{
	m_textblockText.setCharacterSize(CharSize);
}

void Textblock::fixCharsize()
{
	// Charsizes over 23 == problems --> fix
	if(m_textblockText.getCharacterSize() > 23)
	{
		m_textblockText.move(0, -3);
	}
}

std::string Textblock::lineBreak(String S, Vector2f size)
{
	std::string tmp_word;
	std::string tmp_line;
	int count = 0;
	std::string biggest;
	std::string tmp;
	std::string output;

	for(unsigned int i = 0; i < S.getSize(); i++)
	{
		while(S[i + count] != ' ' || S[i + count] == '\0')
		{
			tmp_word += S[i + count];
			count++;

			if(count + i == S.getSize())
				break;
		}
		if(i + count != S.getSize())
		{
			tmp_word += ' ';
		}
		tmp_line += tmp_word;
		m_textblockText.setString(tmp_line);
		textsize = m_textblockText.getLocalBounds();

		if(size.x < textsize.width)
		{
			output += '\n';
			output += tmp_word;
			tmp_line = tmp_word;
			tmp_word.clear();
		}
		output += tmp_word;
		tmp_word.clear();

		i += count;
		count = 0;
	}

	return output;
}

void Textblock::operator=(const Textblock & tblock)
{
	setSize(tblock.getSize());
	setPosition(tblock.getPosition());

	m_ID = tblock.m_ID;

	m_color = tblock.m_color;

	m_textblockText = tblock.m_textblockText;
}

void Textblock::draw(RenderWindow* rw)
{
	rw->draw(*this);
	rw->draw(m_textblockText);
}