#include "IngameView.h"

//TODO update constructor 
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

	m_turnOn = false;
	
	
	
	u = new Unit(Vector2f(500,500),UnitTypes::HEAVY, 120);
	m_ClickV.push_back(u);
	m_DrawV.push_back(u);

	u1 = new Unit(Vector2f(570,500),UnitTypes::LIGHT, 17);
	m_ClickV.push_back(u1);
	m_DrawV.push_back(u1);
	//debug end
	
	m_map.load("Data/Maps/TestMap.tmx");
	m_tileSize = Vector2i(m_map.layers[0]->TileWidth, m_map.layers[0]->TileHeight) * 2;
	m_mapSize = Vector2i(m_map.layers[0]->layer[0].size(), m_map.layers[0]->layer.size()) / 2;
	m_mapTotalSize = Vector2i(m_tileSize.x * m_mapSize.x, m_tileSize.x * m_mapSize.x); 
	
	//GET STARTING Mapview POSITION
	m_mapView.left = (m_mapTotalSize.x - screensize.x) / 2;
	m_mapView.top = (m_mapTotalSize.y - screensize.y) / 2;
	m_mapView.width = screensize.x;
	m_mapView.height = screensize.y;


	//Interface Goes Here
	m_commitB = new CommitButton(Vector2f(0,0), Vector2f(0,0), "commit", static_cast<int>(IngameViewButtonId::COMMIT),false, screensize);
	m_commitB->Attach(this);
	m_DrawV.push_back(m_commitB);
	m_ClickV.push_back(m_commitB); 
	m_AnimateV.push_back(m_commitB);

	
	//SBAR 
	m_SBar = new Statusbar(Vector2f(0, 0), Vector2f(static_cast<float>(screensize.x), Statusbarheight), SBar_Function); 
	m_DrawV.push_back(m_SBar);
	m_ClickV.push_back(m_SBar);
	m_AnimateV.push_back(m_SBar);

	m_mapMouseOver.setOutlineColor(MyColors.WhiteTransparent);
	m_mapMouseOver.setOutlineThickness(INGAMEVIEW_MOUSEOVER_RECT_BORDER);
	m_mapMouseOver.setFillColor(MyColors.Transparent);
	m_mapMouseOver.setSize(Vector2f(static_cast<float>(m_tileSize.x - INGAMEVIEW_MOUSEOVER_RECT_BORDER * 2), static_cast<float>(m_tileSize.y - INGAMEVIEW_MOUSEOVER_RECT_BORDER * 2)));
	

	m_turnOn=true;
	rsTurn.setOutlineThickness(INGAMEVIEW_MOUSEOVER_RECT_BORDER);
	rsTurn.setFillColor(MyColors.Transparent);
	rsTurn.setSize(Vector2f(static_cast<float>(m_tileSize.x - INGAMEVIEW_MOUSEOVER_RECT_BORDER * 2), static_cast<float>(m_tileSize.y - INGAMEVIEW_MOUSEOVER_RECT_BORDER * 2)));

	for(auto it : m_map.layers)
		if(it->isBarricadeLayer)
			collisionLayer=it;
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
	case IngameViewButtonId::COMMIT:
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
	
	m_pointAt.x = (m_pointAt.x>=m_mapSize.x)?m_mapSize.x-1:m_pointAt.x;
	m_pointAt.y = (m_pointAt.y>=m_mapSize.y)?m_mapSize.y-1:m_pointAt.y;
	m_pointAt.x = (m_pointAt.x<0)?0:m_pointAt.x;
	m_pointAt.y = (m_pointAt.y<0)?0:m_pointAt.y;
	
	m_mapMouseOver.setPosition( static_cast<float>(m_pointAt.x * m_tileSize.x + INGAMEVIEW_MOUSEOVER_RECT_BORDER - m_mapView.left), 
								static_cast<float>(m_pointAt.y * m_tileSize.y + INGAMEVIEW_MOUSEOVER_RECT_BORDER - m_mapView.top));
	return retValue;
}

bool IngameView::PressedRight()
{
	drawPath();

	for(unsigned int i = 0; i < m_ClickV.size(); i++)
		if(m_ClickV[i]->PressedRight())
			return true;
	return false;
}

bool IngameView::PressedLeft()
{
	currentTurn.clear();
	bool retvalue = false;
	for(unsigned int i = 0; i < m_ClickV.size(); i++)
		if(m_ClickV[i]->PressedLeft())
			return true;

	for(unsigned int i = 0; i < m_GameData.ownedCities.size(); i++)
		if(m_pointAt == m_GameData.ownedCities[i]->position)
			displayCityInfo(*m_GameData.ownedCities[i]);
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
	
	for(auto it : currentTurn)
	{
		rsTurn.setPosition( static_cast<float>(it.pos.x * m_tileSize.x + INGAMEVIEW_MOUSEOVER_RECT_BORDER - m_mapView.left), 
							static_cast<float>(it.pos.y * m_tileSize.y + INGAMEVIEW_MOUSEOVER_RECT_BORDER - m_mapView.top));
		if(it.valid)
		{
			rsTurn.setOutlineColor(Color(0x0F,0x99,0x00,0xFF));
			rsTurn.setFillColor(Color(0x0F,0x99,0x00,0x77));
		}
		else
		{
			rsTurn.setOutlineColor(Color(0xFF,0x1F,0x1F,0xFF));
			rsTurn.setFillColor(Color(0xFF,0x1F,0x1F,0x77));
		}
		rw->draw(rsTurn);
	}

	rw->draw(m_mapMouseOver);

	Rect<float> MapView;
	m_mapView.width= rw->getSize().x;
	m_mapView.height = rw->getSize().y;
}

Views IngameView::nextState()
{
	return m_nextView;
}

void IngameView::update(double elapsedMs)
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
	case InagameViewPhases::YOURTURN:
		m_commitB->setIsEnabled(false);
		//do things..
		//send moves to server
		m_phase = InagameViewPhases::WAITFORPLAYERS;
		break;

	case InagameViewPhases::WAITFORPLAYERS:
		//do things..
		//wait till server sends move data
		m_phase = InagameViewPhases::WATCHRESULTS;
		break;

	case InagameViewPhases::WATCHRESULTS:
		//on player button click
		m_commitB->setIsEnabled(true);
		//do things..
		m_phase = InagameViewPhases::YOURTURN;
		break;

	case InagameViewPhases::GAMEOVER:
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
	m_mapView.left += static_cast<int>(m_scrollspeed.x * _x);

	if(m_mapTotalSize.x > static_cast<int>(m_screensize.x))
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
	m_mapView.top += static_cast<int>(m_scrollspeed.y * _y); 

	if(m_mapTotalSize.y > static_cast<int>(m_screensize.y))
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

void IngameView::displayCityInfo(City &c)
{
	std::cout << " stadt Income : " << c.generatedIncome << std::endl;
	std::cout << " stadt level  : " << c.level << std::endl;
}

void IngameView::displayArmyInfo(Unit &)
{
	std::cout << " clicked on army! " << std::endl;
}

void IngameView::drawPath()
{
	if(m_turnOn)
	{
		m_is_turn_valid = true;

		if(currentTurn.size() == 0)
		{
			m_maxLen=10;
			currentTurn.push_back(turn(m_pointAt));
		}
		else
		{
			sf::Vector2i lastTurn = currentTurn.back().pos;
			if(m_pointAt != lastTurn)
			{
				sf::Vector2i diff;
				while(lastTurn != m_pointAt && m_maxLen > static_cast<short>(currentTurn.size()))
				{
					diff=m_pointAt-lastTurn;
					if(diff.x != 0)
					{
						lastTurn+=sf::Vector2i(diff.x>0?1:-1,0);
						currentTurn.push_back(lastTurn);
						if(	collisionLayer->layer[lastTurn.y*2][lastTurn.x*2] != 0 || collisionLayer->layer[lastTurn.y*2][lastTurn.x*2+1] != 0 ||
							collisionLayer->layer[lastTurn.y*2+1][lastTurn.x*2] != 0 || collisionLayer->layer[lastTurn.y*2+1][lastTurn.x*2+1] != 0)
						{
							currentTurn.back().valid = false;
							m_is_turn_valid = false;
						}
					}
					if( m_maxLen <= static_cast<short>(currentTurn.size()))
						break;
					if(diff.y != 0)
					{
						lastTurn+=sf::Vector2i(0,diff.y>0?1:-1);
						currentTurn.push_back(lastTurn);
						if(	collisionLayer->layer[lastTurn.y*2][lastTurn.x*2] != 0 || collisionLayer->layer[lastTurn.y*2][lastTurn.x*2+1] != 0 ||
							collisionLayer->layer[lastTurn.y*2+1][lastTurn.x*2] != 0 || collisionLayer->layer[lastTurn.y*2+1][lastTurn.x*2+1] != 0)
						{
							currentTurn.back().valid=false;
						}
					}
				}
			}
		}
	}
}
