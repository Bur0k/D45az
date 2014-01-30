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

	m_turnOnPathDraw = false;
	
	
	
	u = new Unit(Vector2f(500,500),UnitTypes::HEAVY, 120);
	m_ClickV.push_back(u);
	m_DrawV.push_back(u);

	u1 = new Unit(Vector2f(570,500),UnitTypes::LIGHT, 17);
	m_ClickV.push_back(u1);
	m_DrawV.push_back(u1);
	//debug end
	
	m_map.load("Data/Maps/Map1.tmx");
	m_tileSize = Vector2i(m_map.layers[0]->TileWidth, m_map.layers[0]->TileHeight) * 2;
	m_mapTileSize = Vector2i(m_map.layers[0]->TileWidth, m_map.layers[0]->TileHeight);
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
	

	m_turnOnPathDraw=true;
	rsTurn.setOutlineThickness(INGAMEVIEW_MOUSEOVER_RECT_BORDER);
	rsTurn.setFillColor(MyColors.Transparent);
	rsTurn.setSize(Vector2f(static_cast<float>(m_tileSize.x - INGAMEVIEW_MOUSEOVER_RECT_BORDER * 2), static_cast<float>(m_tileSize.y - INGAMEVIEW_MOUSEOVER_RECT_BORDER * 2)));

	for(auto it : m_map.layers)
		if(it->isBarricadeLayer)
			collisionLayer=it;

	updateNewFogOfWar = true;
	turnOnFogOfWar = true;

	m_GameData.ownedCities.push_back(new City(sf::Vector2i(2,2),1));

	updateFogOfWar();
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

	if(currentTurn.size() != 0)
	{
		if(m_turnOnPathDraw)
		{

			m_is_turn_valid = true;

			mouseOverTurn.clear();
			sf::Vector2i lastTurn = currentTurn.back().pos;
			if(m_pointAt != lastTurn)
			{
				sf::Vector2i diff;
				while(lastTurn != m_pointAt && m_maxLen > static_cast<short>(mouseOverTurn.size()+currentTurn.size()))
				{
					diff=m_pointAt-lastTurn;
					if(diff.x != 0)
					{
						lastTurn+=sf::Vector2i(diff.x>0?1:-1,0);
						mouseOverTurn.push_back(lastTurn);
						if(	collisionLayer->layer[lastTurn.y*2][lastTurn.x*2] != 0 || collisionLayer->layer[lastTurn.y*2][lastTurn.x*2+1] != 0 ||
							collisionLayer->layer[lastTurn.y*2+1][lastTurn.x*2] != 0 || collisionLayer->layer[lastTurn.y*2+1][lastTurn.x*2+1] != 0)
						{
							mouseOverTurn.back().valid = false;
							m_is_turn_valid = false;
						}
					}
					if( m_maxLen <= static_cast<short>(mouseOverTurn.size()+currentTurn.size()))
						break;
					if(diff.y != 0)
					{
						lastTurn+=sf::Vector2i(0,diff.y>0?1:-1);
						mouseOverTurn.push_back(lastTurn);
						if(	collisionLayer->layer[lastTurn.y*2][lastTurn.x*2] != 0 || collisionLayer->layer[lastTurn.y*2][lastTurn.x*2+1] != 0 ||
							collisionLayer->layer[lastTurn.y*2+1][lastTurn.x*2] != 0 || collisionLayer->layer[lastTurn.y*2+1][lastTurn.x*2+1] != 0)
						{
							mouseOverTurn.back().valid=false;
						}
					}
				}
			}
		}
	}
	return retValue;
}

bool IngameView::PressedRight()
{
	drawPath();

	if(m_is_turn_valid)
		addPathToArmy();

	for(unsigned int i = 0; i < m_ClickV.size(); i++)
		if(m_ClickV[i]->PressedRight())
			return true;
	return false;
}

bool IngameView::PressedLeft()
{
	currentTurn.clear();
	mouseOverTurn.clear();

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

	if(turnOnFogOfWar)
	{
		rsTurn.setFillColor(Color(0x00,0x00,0x00,0xAA));
		rsTurn.setOutlineColor(Color(0x00,0x00,0x00,0x00));
		rsTurn.setSize(Vector2f(static_cast<float>(m_mapTileSize.x), static_cast<float>(m_mapTileSize.y)));

		int width=m_mapView.width / m_mapTileSize.x + 1 +
		((m_mapView.top+m_mapView.width % m_mapTileSize.x  > 0)? 1 : 0);

		int height=m_mapView.height / m_mapTileSize.y + 1 +
			((m_mapView.left+m_mapView.height  % m_mapTileSize.y > 0)? 1 : 0) ;

		int firstY=m_mapView.top/m_mapTileSize.y;
		int firstX=m_mapView.left/m_mapTileSize.x;

		if(firstX<0)
		{
			width-=firstX;
			firstX=0;
		}
	#pragma warning( push )
	#pragma warning( disable: 4018 )//Hier stimmt alles
		while(firstX > m_map.layers[0]->layer[0].size())
			firstX--;
		while(firstX+width > m_map.layers[0]->layer[0].size())
			width--;

		if(firstY<0)
		{
			height-=firstY;
			firstY=0;
		}
		while(firstY > m_map.layers[0]->layer.size())
			firstY--;
		while(firstY+height > m_map.layers[0]->layer.size())
			height--;
	 #pragma warning( pop )

		for(int y=firstY ; y!=firstY+height ; y++)
		{
			for(int x=firstX ; x!=firstX+width ; x++)
			{
				if(toDraw[y][x])
				{
					rsTurn.setPosition((float)x*m_mapTileSize.x-m_mapView.left,(float)y*m_mapTileSize.y-m_mapView.top);
					rw->draw(rsTurn);
				}
			}
		}
	}
	
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
	for(auto it : mouseOverTurn)
	{
		rsTurn.setPosition( static_cast<float>(it.pos.x * m_tileSize.x + INGAMEVIEW_MOUSEOVER_RECT_BORDER - m_mapView.left), 
							static_cast<float>(it.pos.y * m_tileSize.y + INGAMEVIEW_MOUSEOVER_RECT_BORDER - m_mapView.top));
		if(it.valid)
		{
			rsTurn.setOutlineColor(Color(0x0F,0x99,0x00,0x77));
			rsTurn.setFillColor(Color(0x0F,0x99,0x00,0x22));
		}
		else
		{
			rsTurn.setOutlineColor(Color(0xFF,0x1F,0x1F,0x77));
			rsTurn.setFillColor(Color(0xFF,0x1F,0x1F,0x22));
		}
		rw->draw(rsTurn);
	}

	

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
	
	Rect<int> tmpView = m_mapView;

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

	if(m_mapTotalSize.x  + INGAMEVIEW_SCROLLEXESS * 2 > static_cast<int>(m_screensize.x))
	{
		if(m_mapView.left + m_mapView.width > m_mapTotalSize.x + INGAMEVIEW_SCROLLEXESS)
		{
			m_mapView.left = m_mapTotalSize.x - m_mapView.width + INGAMEVIEW_SCROLLEXESS;
			m_scrollspeed.x = 0;
		}
		else if(m_mapView.left + INGAMEVIEW_SCROLLEXESS < 0)
		{
			m_mapView.left = - INGAMEVIEW_SCROLLEXESS;
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

	if(m_mapTotalSize.y + INGAMEVIEW_SCROLLEXESS * 2 > static_cast<int>(m_screensize.y))
	{	
		if(m_mapView.top + m_mapView.height > m_mapTotalSize.y + INGAMEVIEW_SCROLLEXESS)
		{
			m_mapView.top = m_mapTotalSize.y - m_mapView.height + INGAMEVIEW_SCROLLEXESS;
			m_scrollspeed.y = 0;
		}
		else if(m_mapView.top + INGAMEVIEW_SCROLLEXESS < 0)
		{
			m_mapView.top = - INGAMEVIEW_SCROLLEXESS;
			m_scrollspeed.y = 0;
		}
	}

	//update armys
	if(tmpView != m_mapView)
	{
		for(unsigned int i = 0; i < m_owned_armys.size(); i++)
			m_owned_armys[i]->m_mapViewOffset = Vector2i(m_mapView.left, m_mapView.top);
		for(unsigned int i = 0; i < m_enemy_armys.size(); i++)
			m_enemy_armys[i]->m_mapViewOffset = Vector2i(m_mapView.left, m_mapView.top);
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
	if(m_turnOnPathDraw)
	{
		m_is_turn_valid = true;
		mouseOverTurn.clear();

		if(currentTurn.size() == 0)
		{
			m_maxLen=10;
			currentTurn.push_back(turn(m_pointAt));
			if(	collisionLayer->layer[currentTurn.back().pos.y*2][currentTurn.back().pos.x*2] != 0 || collisionLayer->layer[currentTurn.back().pos.y*2][currentTurn.back().pos.x*2+1] != 0 ||
				collisionLayer->layer[currentTurn.back().pos.y*2+1][currentTurn.back().pos.x*2] != 0 || collisionLayer->layer[currentTurn.back().pos.y*2+1][currentTurn.back().pos.x*2+1] != 0)
			{
				currentTurn.back().valid = false;
				m_is_turn_valid = false;
			}
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

void IngameView::addPathToArmy()
{
	for(auto turns : army_moves)
	{
		if(currentTurn[0].pos == turns[0])
		{
			turns.clear();
			for(auto turn : currentTurn)
				turns.push_back(turn.pos);
			return;
		}
					}
	
	std::vector<sf::Vector2i> newturn;
		
	for(auto turn : currentTurn)
		newturn.push_back(turn.pos);
	army_moves.push_back(newturn);
				}

void IngameView::loadPath(Vector2i pos)
{
	for(auto turns : army_moves)
	{
		if(turns[0] ==  pos)
		{
			currentTurn.clear();
			for(auto move : turns)
				currentTurn.push_back(turn(move));
			break;
			}
		}
	}
}

void IngameView::updateFogOfWar()
{
	updateNewFogOfWar = false;

	toDraw.clear();
	std::vector<bool> temp;
	temp.resize(m_map.layers[0]->layer[0].size(),true);//X Values
	for(int i=0;i<m_map.layers[0]->layer.size();i++)//Y Values
		toDraw.push_back(temp);

	for(auto it:m_GameData.ownedUnits)
	{
		short maxRange = 0;
		switch(it->units->type)
		{
		case UnitTypes::ARTILLERY:
			maxRange=INGAMEVIEW_ARTILLERY_SIGHT>maxRange?INGAMEVIEW_ARTILLERY_SIGHT:maxRange;
		case UnitTypes::HEAVY:
			maxRange=INGAMEVIEW_HEAVY_SIGHT>maxRange?INGAMEVIEW_HEAVY_SIGHT:maxRange;
		case UnitTypes::LIGHT:
			maxRange=INGAMEVIEW_LIGHT_SIGHT>maxRange?INGAMEVIEW_LIGHT_SIGHT:maxRange;
		case UnitTypes::LONGRANGE:
			maxRange=INGAMEVIEW_RANGED_SIGHT>maxRange?INGAMEVIEW_RANGED_SIGHT:maxRange;
			}
		for(int i=0;i<m_map.layers[0]->layer.size();i++)
			for(int j=0;j<m_map.layers[0]->layer[0].size();j++)
				if((j-it->pos.x)*(j-it->pos.x) + 
					(i-it->pos.y)*(i-it->pos.y) <= maxRange*maxRange)
					toDraw[i][j]=false;
		}
	for(auto it2:m_map.layers)
		if(it2->isCityTerrainLayer)//Wird nur ein Layer durchgehen ab hier
			for(auto it3:m_GameData.ownedCities)
			{
				int id = it2->layer[it3->position.y][it3->position.x];
				for(int i=0;i<it2->layer.size();i++)
					for(int j=0;j<it2->layer[0].size();j++)
						if(id == it2->layer[i][j])
							toDraw[i][j]=false;
	}

void IngameView::loadArmys()
{
	for(Army* army : m_owned_armys)
		delete army;
	
	for(unsigned int i = 0; i < m_GameData.ownedUnits.size(); i++)
		m_owned_armys.push_back(new Army(1));

}


