#include "IngameView.h"

IngameView::IngameView(Vector2u & screensize)
{
	//debug 
	m_nextView = Views::NOCHANGE;
	u = new Unit(Vector2f(500,500),UnitTypes::LONGRANGE,120);
	m_ClickV.push_back(u);
	m_DrawV.push_back(u);

	u1 = new Unit(Vector2f(570,500),UnitTypes::ARTILLERY,17);
	m_ClickV.push_back(u1);
	m_DrawV.push_back(u1);
	//debug end

	m_map.load("Data/Maps/test.tmx");
	m_map.layers[0]->TileHeight;
	
}

IngameView::~IngameView()
{
	delete u;
	delete u1;
}


void IngameView::onButtonClick(int id)
{
	switch (id)
	{
	default:
		break;
	}
}

void IngameView::onSliderValueChange(int ID, double position)
{
	//DO SOMETHING
}

void IngameView::onSliderReleased(int ID, double position)
{
	//DO SOMETHING
}

void IngameView::onTextBoxSend(int ID, std::string s)
{

}



bool IngameView::MouseMoved(sf::Vector2i & mouse)
{
	for(unsigned int i = 0; i < m_ClickV.size(); i++)
		if(m_ClickV[i]->MouseMoved(mouse))
			return true;
	return false;
}

bool IngameView::PressedRight()
{
	for(unsigned int i = 0; i < m_ClickV.size(); i++)
		if(m_ClickV[i]->PressedRight())
			return true;
	return false;
}

bool IngameView::PressedLeft()
{
	for(unsigned int i = 0; i < m_ClickV.size(); i++)
		if(m_ClickV[i]->PressedLeft())
			return true;
	return false;
}

bool IngameView::ReleasedRight()
{
	for(unsigned int i = 0; i < m_ClickV.size(); i++)
		if(m_ClickV[i]->ReleasedRight())
			return true;
	return false;
}

bool IngameView::ReleasedLeft()
{
	for(unsigned int i = 0; i < m_ClickV.size(); i++)
		if(m_ClickV[i]->ReleasedLeft())
			return true;
	return false;
}
	
void IngameView::animationTick()
{
	for(unsigned int i = 0; i < m_AnimateV.size(); i++)
		m_AnimateV[i]->animationTick();
}
	
void IngameView::onKeyDown(sf::Event e)
{
	for(unsigned int i = 0; i < m_KeyV.size(); i++)
		m_KeyV[i]->onKeyDown(e);
}

void IngameView::onKeyUp(sf::Event e)
{
	for(unsigned int i = 0; i < m_KeyV.size(); i++)
		m_KeyV[i]->onKeyUp(e);
}
void IngameView::onTextInput(std::string s)
{
	for(unsigned int i = 0; i < m_KeyV.size(); i++)
		m_KeyV[i]->onTextInput(s);
}

void IngameView::draw(sf::RenderWindow* rw)
{
	for(unsigned int i = 0; i < m_DrawV.size(); i++)
		m_DrawV[i]->draw(rw);	
	
	Rect<float> MapView;
	m_mapView.width= rw->getSize().x;
	m_mapView.height = rw->getSize().y;

	m_map.render(*rw,m_mapView);
}

Views IngameView::nextState()
{
	return m_nextView;
}

void IngameView::update(double elpasedMs)
{
	//BURAK GOES HERE
}

void IngameView::onResize(Vector2u & size)
{
	
}

Views IngameView::getType()
{
	return Views::INGAME;
}

