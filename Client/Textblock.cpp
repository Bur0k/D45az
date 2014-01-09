#include "Textblock.h"

Textblock::Textblock()
{
	//TODO
}

Textblock::~Textblock()
{

}

Textblock::Textblock(Vector2f pos, Vector2f size, String S, int ID)
{
	m_ID = ID;

	setSize(size);
	setPosition(pos);
	m_Font = Font(MyFonts.Arial);
	m_textblockText.setFont(m_Font);
	m_textblockText.setString(S);
	m_textblockText.setPosition(getPosition());
	m_textblockText.setColor(MyColors.Orange);

	sf::Rect<float> textsize;

	while(true)
	{
		textsize = m_textblockText.getLocalBounds();
		float scale = m_textblockText.getScale().x;
		if(textsize.width * scale > size.x || textsize.height * scale > size.y)
		{
			scale *= 0.8f;
			m_textblockText.setScale(scale, scale);
		}
		else
			break;
	}

	m_textblockText.move(	(getSize().x - textsize.width * m_textblockText.getScale().x) / 2.0f,
							(getSize().y - textsize.height * 1.5f * m_textblockText.getScale().y) / 2.0f);

	m_color = MyColors.White;
	setFillColor(m_color);
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