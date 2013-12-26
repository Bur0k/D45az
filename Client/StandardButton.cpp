#include "StandardButton.h"

StandardButton::StandardButton()
{
	//TODO
}

StandardButton::StandardButton(Vector2f pos, Vector2f size, sf::String S, int ID) 
	: Button(pos, size, S, ID)
{
	m_pST = new SpriteTex[8];

	//TODO REPEAT TEXTURES NOT stretch them
	// LOAD TEXTURE
	Image img;
	if(!img.loadFromFile("Data/Images/Button.png"))
		std::cout << "standardbutton: Load Image Failed!" << std::endl;
	
	//select tiles from button tilesheet
	
	m_pST[0].t.loadFromImage(img, IntRect(0, 0, BUTTONTILESIZE, BUTTONTILESIZE));
	m_pST[1].t.loadFromImage(img, IntRect(BUTTONTILESIZE, 0, BUTTONTILESIZE, BUTTONTILESIZE));
	m_pST[2].t.loadFromImage(img, IntRect(BUTTONTILESIZE * 2, 0, BUTTONTILESIZE, BUTTONTILESIZE));
	m_pST[3].t.loadFromImage(img, IntRect(0, BUTTONTILESIZE, BUTTONTILESIZE, BUTTONTILESIZE));
	m_pST[4].t.loadFromImage(img, IntRect(BUTTONTILESIZE * 2, BUTTONTILESIZE, BUTTONTILESIZE, BUTTONTILESIZE));
	m_pST[5].t.loadFromImage(img, IntRect(0, BUTTONTILESIZE * 2, BUTTONTILESIZE, BUTTONTILESIZE));
	m_pST[6].t.loadFromImage(img, IntRect(BUTTONTILESIZE, BUTTONTILESIZE * 2, BUTTONTILESIZE, BUTTONTILESIZE));
	m_pST[7].t.loadFromImage(img, IntRect(BUTTONTILESIZE * 2, BUTTONTILESIZE * 2, BUTTONTILESIZE * 2, BUTTONTILESIZE));
	
	//load texture to sf::RectangleShapes

	for(int i = 0; i < 8; i++)
	{
		m_pST[i].t.setSmooth(false);
		m_pST[i].t.setRepeated(true);
		m_pST[i].s.setTexture(&m_pST[i].t, true);
		m_pST[i].s.setPosition(getPosition());
	}

	//move sprites to position and scale it appropriately

	m_pST[0].s.setSize(Vector2f(BUTTONTILESIZE, BUTTONTILESIZE));
	m_pST[1].s.move(BUTTONTILESIZE, 0);
	m_pST[1].s.setSize(Vector2f(size.x - BUTTONTILESIZE * 2, BUTTONTILESIZE));
	m_pST[2].s.move(size.x - BUTTONTILESIZE, 0);
	m_pST[2].s.setSize(Vector2f(BUTTONTILESIZE, BUTTONTILESIZE));
	m_pST[3].s.move(0, BUTTONTILESIZE);
	m_pST[3].s.setSize(Vector2f(BUTTONTILESIZE, size.y - BUTTONTILESIZE * 2));
	m_pST[4].s.move(size.x - BUTTONTILESIZE, BUTTONTILESIZE);
	m_pST[4].s.setSize(Vector2f(BUTTONTILESIZE, size.y - BUTTONTILESIZE * 2));
	m_pST[5].s.move(0, size.y - BUTTONTILESIZE);
	m_pST[5].s.setSize(Vector2f(BUTTONTILESIZE, BUTTONTILESIZE));
	m_pST[6].s.move( BUTTONTILESIZE,size.y - BUTTONTILESIZE);
	m_pST[6].s.setSize(Vector2f(size.x - BUTTONTILESIZE * 2, BUTTONTILESIZE));
	m_pST[7].s.move(size.x - BUTTONTILESIZE, size.y - BUTTONTILESIZE);
	m_pST[7].s.setSize(Vector2f(BUTTONTILESIZE, BUTTONTILESIZE));
	
	// positioning
	
	updateVisuals(false);

	//define backgroundrect

	m_Rect.setFillColor(m_color);
	m_Rect.setSize(Vector2f(size.x - BUTTONTILESIZE, size.y - BUTTONTILESIZE));
	m_Rect.setPosition(pos.x + BUTTONTILESIZE / 2, pos.y + BUTTONTILESIZE / 2);
}

StandardButton::~StandardButton()
{
	delete[] m_pST;
}

void StandardButton::updateVisuals(bool colorCange)
{

	m_Rect.setFillColor(getFillColor());

	if(!colorCange)
	{
		m_Rect.setPosition(getPosition().x + BUTTONTILESIZE,
						   getPosition().y + BUTTONTILESIZE);
		m_Rect.setSize(Vector2f(getSize().x - BUTTONTILESIZE * 2,
								getSize().y - BUTTONTILESIZE * 2));
	}


}

void StandardButton::draw(RenderWindow* rw)
{
	//TODO move button visuals when parent position changed

	rw->draw(m_Rect);

	for(int i = 0; i < 8; i++)
		rw->draw(m_pST[i].s);

	rw->draw(m_buttonText);

}