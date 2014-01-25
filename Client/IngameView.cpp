#include "IngameView.h"

IngameView::IngameView(Vector2u & screensize, StatusBarFunctions* SBar_Function, InagameViewPhases startphase)
{
	m_nextView = Views::NOCHANGE;

	m_screensize = screensize;

	m_activeAt = Vector2i(-1,-1);
	m_pointAt = Vector2i(-1,-1);
	m_scrolldir = Vector2i(0,0);
	m_scrollspeed = Vector2f(0,0);

	m_phase = startphase;
	//debug
	
	
	u = new Unit(Vector2f(500,500),UnitTypes::LONGRANGE, 120);
	m_ClickV.push_back(u);
	m_DrawV.push_back(u);

	u1 = new Unit(Vector2f(570,500),UnitTypes::ARTILLERY, 17);
	m_ClickV.push_back(u1);
	m_DrawV.push_back(u1);
	//debug end
	
	m_map.load("Data/Maps/test.tmx");
	m_tileSize = Vector2i(m_map.layers[0]->TileWidth, m_map.layers[0]->TileHeight);
	m_mapSize = Vector2i(m_map.layers[0]->layer[0].size(), m_map.layers[0]->layer.size());
	m_mapTotalSize = Vector2i(m_tileSize.x * m_mapSize.x, m_tileSize.x * m_mapSize.x); 
	
	//GET STARTING Mapview POSITION
	m_mapView.left = (m_mapTotalSize.x - screensize.x) / 2;
	m_mapView.top = (m_mapTotalSize.y - screensize.y) / 2;
	m_mapView.width = screensize.x;
	m_mapView.height = screensize.y;


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

	m_mapMouseOver.setOutlineColor(MyColors.WhiteTransparent);
	m_mapMouseOver.setOutlineThickness(INGAMEVIEW_MOUSEOVER_RECT_BORDER);
	m_mapMouseOver.setFillColor(MyColors.Transparent);
	m_mapMouseOver.setSize(Vector2f(m_tileSize.x - INGAMEVIEW_MOUSEOVER_RECT_BORDER * 2, m_tileSize.y - INGAMEVIEW_MOUSEOVER_RECT_BORDER * 2));
	
}

IngameView::~IngameView()
{
	delete u;
	delete u1;
	delete m_SBar;
	delete m_commitB;
}


void IngameView::onButtonClick(int id)
{
	switch (id)
	{
	case COMMIT:
		if(m_phase == InagameViewPhases::YOURTURN)
			nextPhase();
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
	bool retValue = false;
	for(unsigned int i = 0; i < m_ClickV.size(); i++)
		if(m_ClickV[i]->MouseMoved(mouse))
			retValue = true;
	
	//where does the user point?
	m_pointAt.x = (mouse.x + m_mapView.left) / m_tileSize.x;
	m_pointAt.y = (mouse.y + m_mapView.top) / m_tileSize.y;
	
	

	m_mapMouseOver.setPosition( m_pointAt.x * m_tileSize.x + INGAMEVIEW_MOUSEOVER_RECT_BORDER - m_mapView.left, 
								m_pointAt.y * m_tileSize.y + INGAMEVIEW_MOUSEOVER_RECT_BORDER - m_mapView.top);
	
	return retValue;
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
	bool retvalue = false;
	for(unsigned int i = 0; i < m_ClickV.size(); i++)
		if(m_ClickV[i]->PressedLeft())
			retvalue = true;

	return retvalue;
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

	moveMap();
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
	
	rw->draw(m_mapMouseOver);

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
	//GIVE ME INFO DAMMIT!

}

void IngameView::onResize(Vector2u & size)
{
	m_screensize = size;
	m_SBar->Resize((Vector2f) size);
	m_commitB->onResize(size);
	m_mapView.width = size.x;
	m_mapView.height = size.y;
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
		m_commitB->setIsEnabled(false);
		//do things..
		//send moves to server
		m_phase = WAITFORPLAYERS;
		break;

	case WAITFORPLAYERS:
		//do things..
		//wait till server sends move data
		m_phase = WATCHRESULTS;
		break;

	case WATCHRESULTS:
		//on player button click
		m_commitB->setIsEnabled(true);
		//do things..
		m_phase = YOURTURN;
		break;

	case GAMEOVER:
		//do things..
		//remove fow
		std::cout << "This Game has ended!" << std::endl;
		break;

	default:
		std::cout << "IngameView Error: unknow phase!" << std::endl;
		break;
	}
}

void IngameView::setScrollDirection(int x, int y)
{
	m_scrolldir.x  = x;
	m_scrolldir.y = y;
}

void IngameView::moveMap()
{
	static int _x;
	static int _y;
	
	//X
	//increase or decrease the scrollspeed
	m_scrollspeed.x += (m_scrolldir.x != 0)? 1 : -2;
	if(m_scrollspeed.x < 0)
		m_scrollspeed.x = 0;
	else if(m_scrollspeed.x > INGAMEVIEW_MAX_MAPSPEED)
		m_scrollspeed.x = INGAMEVIEW_MAX_MAPSPEED;

	//update the local statics
	if(m_scrolldir.x != 0)
		_x = m_scrolldir.x;
	else if(m_scrollspeed.x == 0)
		_x = 0;

	//move the map or not move if at border

		m_mapView.left += m_scrollspeed.x * _x;
	if(m_mapTotalSize.x > m_screensize.x)
	{
		if(m_mapView.left + m_mapView.width > m_mapTotalSize.x)
		{
			m_mapView.left = m_mapTotalSize.x - m_mapView.width;
			m_scrollspeed.x = 0;
		}
		else if(m_mapView.left < 0)
		{
			m_mapView.left = 0;
			m_scrollspeed.x = 0;
		}
	}

		//Y
		//increase or decrease the scrollspeed
		m_scrollspeed.y += (m_scrolldir.y != 0)? 1 : -2;
		if(m_scrollspeed.y < 0)
			m_scrollspeed.y = 0;
		else if(m_scrollspeed.y > INGAMEVIEW_MAX_MAPSPEED)
			m_scrollspeed.y = INGAMEVIEW_MAX_MAPSPEED;

		//update the local statics
		if(m_scrolldir.y != 0)
			_y = m_scrolldir.y;
		else if(m_scrollspeed.y == 0)
			_y = 0;

		//move the map or not move if at border
		m_mapView.top += m_scrollspeed.y * _y; 
	if(m_mapTotalSize.y > m_screensize.y)
	{	
		if(m_mapView.top + m_mapView.height > m_mapTotalSize.y)
		{
			m_mapView.top = m_mapTotalSize.y - m_mapView.height;
			m_scrollspeed.y = 0;
		}
		else if(m_mapView.top < 0)
		{
			m_mapView.top = 0;
			m_scrollspeed.y = 0;
		}
	}
}

