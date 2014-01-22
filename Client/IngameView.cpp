#include "IngameView.h"

IngameView::IngameView(Vector2u & screensize, StatusBarFunctions* SBar_Function)
{
	m_nextView = Views::NOCHANGE;

	//debug 
	
	u = new Unit(Vector2f(500,500),UnitTypes::LONGRANGE,120);
	m_ClickV.push_back(u);
	m_DrawV.push_back(u);

	u1 = new Unit(Vector2f(570,500),UnitTypes::ARTILLERY,17);
	m_ClickV.push_back(u1);
	m_DrawV.push_back(u1);
	//debug end
	
	m_map.load("Data/Maps/test.tmx");
	m_tileSize = Vector2i(m_map.layers[0]->TileWidth, m_map.layers[0]->TileHeight);
	m_mapSize = Vector2i(m_map.layers[0]->layer[0].size(), m_map.layers[0]->layer.size());
	m_mapTotalSize = Vector2i(m_tileSize.x * m_mapSize.x, m_tileSize.x * m_mapSize.x); 
	
	

	//Interface Goes Here
	m_commitB = new CommitButton(Vector2f(0,0), Vector2f(0,0), "commit", COMMIT,false, screensize);
	m_commitB->Attach(this);
	m_DrawV.push_back(m_commitB);
	m_ClickV.push_back(m_commitB); 
	m_AnimateV.push_back(m_commitB);

	
	//SBAR 
	m_SBar = new Statusbar(Vector2f(0, 0), Vector2f(screensize.x, Statusbarheight), SBar_Function); 
	m_DrawV.push_back(m_SBar);
	m_ClickV.push_back(m_SBar);
	m_AnimateV.push_back(m_SBar);
}

IngameView::~IngameView()
{
	delete u;
	delete u1;
	delete m_SBar;
}


void IngameView::onButtonClick(int id)
{
	switch (id)
	{
	case COMMIT:
		m_commitB->setIsEnabled(false);
		break;
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
	m_map.render(*rw,m_mapView);
	for(unsigned int i = 0; i < m_DrawV.size(); i++)
		m_DrawV[i]->draw(rw);	
	
	Rect<float> MapView;
	m_mapView.width= rw->getSize().x;
	m_mapView.height = rw->getSize().y;

	
}

Views IngameView::nextState()
{
	return m_nextView;
}

void IngameView::pt1zyklisch(double elpasedMs)
{
	//LOADING STUFF GOES HERE
}

void IngameView::onResize(Vector2u & size)
{
	m_SBar->Resize((Vector2f) size);
	m_commitB->onResize(size);
}

Views IngameView::getType()
{
	return Views::INGAME;
}

void IngameView::nextPhase()
{
	switch (m_phase)
	{
	case YOURTURN:
		m_phase = WAITFORPLAYERS;
		break;

	case WAITFORPLAYERS:
		m_phase = WATCHRESULTS;
		break;

	case WATCHRESULTS:
		m_phase = YOURTURN;
		m_commitB->setIsEnabled(true);
		break;

	case GAMEOVER:
		std::cout << "This Game has ended!" << std::endl;
		break;

	default:
		std::cout << "IngameView Error: unknow phase!" << std::endl;
		break;
	}
}

void IngameView::MoveMap(int x, int y)
{
	
}

