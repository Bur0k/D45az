#include "StandardButton.h"

StandardButton::StandardButton()
{
	//TODO
}

StandardButton::StandardButton(Vector2f pos, Vector2f size, sf::String S, int ID, bool lock, bool big) 
	: Button(pos, size, S, ID, lock)
{
	m_pST = new SpriteTex[8];

	if(big)
		m_buttonTileSize = 10;
	else
		m_buttonTileSize = 4;

	//TODO REPEAT TEXTURES NOT stretch them
	// LOAD TEXTURE
	Image img;
	if(big)
	{
		if(!img.loadFromFile("Data/Images/Button.png"))
			std::cout << "standardbutton: Load Image Failed!" << std::endl;
	}
	else
	{
		if(!img.loadFromFile("Data/Images/Button_small.png"))
			std::cout << "standardbutton: Load Image Failed!" << std::endl;
	}
		
	//select tiles from button tilesheet
	
	m_pST[0].t.loadFromImage(img, IntRect(0, 0, m_buttonTileSize, m_buttonTileSize));
	m_pST[1].t.loadFromImage(img, IntRect(m_buttonTileSize, 0, m_buttonTileSize, m_buttonTileSize));
	m_pST[2].t.loadFromImage(img, IntRect(m_buttonTileSize * 2, 0, m_buttonTileSize, m_buttonTileSize));
	m_pST[3].t.loadFromImage(img, IntRect(0, m_buttonTileSize, m_buttonTileSize, m_buttonTileSize));
	m_pST[4].t.loadFromImage(img, IntRect(m_buttonTileSize * 2, m_buttonTileSize, m_buttonTileSize, m_buttonTileSize));
	m_pST[5].t.loadFromImage(img, IntRect(0, m_buttonTileSize * 2, m_buttonTileSize, m_buttonTileSize));
	m_pST[6].t.loadFromImage(img, IntRect(m_buttonTileSize, m_buttonTileSize * 2, m_buttonTileSize, m_buttonTileSize));
	m_pST[7].t.loadFromImage(img, IntRect(m_buttonTileSize * 2, m_buttonTileSize * 2, m_buttonTileSize * 2, m_buttonTileSize));
	
	//load texture to sf::RectangleShapes

	for(int i = 0; i < 8; i++)
	{
		m_pST[i].t.setSmooth(false);
		m_pST[i].t.setRepeated(true);
		m_pST[i].s.setTexture(&m_pST[i].t, true);
	}

	//updatePosition();


	// positioning
	
	updatePosition();
	

	//define backgroundrect

	m_Rect.setFillColor(m_color);
	m_Rect.setSize(Vector2f(size.x - m_buttonTileSize, size.y - m_buttonTileSize));
	m_Rect.setPosition(pos.x + m_buttonTileSize / 2, pos.y + m_buttonTileSize / 2);
}

StandardButton::~StandardButton()
{
	delete[] m_pST;
}

void StandardButton::updateVisuals()
{

	m_Rect.setFillColor(getFillColor());
}

void StandardButton::updatePosition()
{
	


	m_Rect.setPosition(getPosition().x + m_buttonTileSize / 2,
						getPosition().y + m_buttonTileSize / 2);
	m_Rect.setSize(Vector2f(getSize().x - m_buttonTileSize,
							getSize().y - m_buttonTileSize));

	for(int i = 0; i < 8; i++)
	{
		m_pST[i].s.setPosition(getPosition());
	}

	//move sprites to position and scale them appropriately
	Vector2f size = this->getSize();


	m_pST[0].s.setSize(Vector2f(m_buttonTileSize, m_buttonTileSize));
	m_pST[1].s.move(m_buttonTileSize, 0);
	m_pST[1].s.setSize(Vector2f(size.x - m_buttonTileSize * 2, m_buttonTileSize));
	m_pST[2].s.move(size.x - m_buttonTileSize, 0);
	m_pST[2].s.setSize(Vector2f(m_buttonTileSize, m_buttonTileSize));
	m_pST[3].s.move(0, m_buttonTileSize);
	m_pST[3].s.setSize(Vector2f(m_buttonTileSize, size.y - m_buttonTileSize * 2));
	m_pST[4].s.move(size.x - m_buttonTileSize, m_buttonTileSize);
	m_pST[4].s.setSize(Vector2f(m_buttonTileSize, size.y - m_buttonTileSize * 2));
	m_pST[5].s.move(0, size.y - m_buttonTileSize);
	m_pST[5].s.setSize(Vector2f(m_buttonTileSize, m_buttonTileSize));
	m_pST[6].s.move( m_buttonTileSize,size.y - m_buttonTileSize);
	m_pST[6].s.setSize(Vector2f(size.x - m_buttonTileSize * 2, m_buttonTileSize));
	m_pST[7].s.move(size.x - m_buttonTileSize, size.y - m_buttonTileSize);
	m_pST[7].s.setSize(Vector2f(m_buttonTileSize, m_buttonTileSize));

	fitText(m_buttonTileSize);
}

void StandardButton::draw(RenderWindow* rw)
{
	// move button visuals when parent position changed
	if( this->getPosition().x != m_Rect.getPosition().x - m_buttonTileSize / 2 ||
		this->getPosition().y != m_Rect.getPosition().y - m_buttonTileSize / 2 ||
		this->getSize().x != m_Rect.getSize().x - m_buttonTileSize * 2 ||
		this->getSize().y != m_Rect.getSize().y - m_buttonTileSize * 2)
		updatePosition();

	rw->draw(m_Rect);

	for(int i = 0; i < 8; i++)
		rw->draw(m_pST[i].s);

	rw->draw(m_buttonText);

}