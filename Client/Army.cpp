#include "Army.h"

Army::Army()
{
	
}

Army::Army(UnitGroup* ug, Rect<int> & mapView, bool isVisible,bool isInCity)
{
	m_animation = -1;
	m_mouseOver = false;
	m_animating = false;

	m_isVisible = isVisible;
	m_marked = false;

	m_playerColor = MyColors.player[ug->player_ID];

	units = ug;
	m_position = Vector2i(ug->pos.x, ug->pos.y);

	Image img;
	if(!img.loadFromFile("Data/Images/germanset.png"))
		std::cout << "Army.cpp : loading of Data/Images/germanset.png failed" << std::endl;
	m_texture = new Texture();
	m_texture->loadFromImage(img);
	m_armySprite = new SplittedSprite(m_texture, ARMY_SPRITE_WIDTH, ARMY_SPRITE_HEIGHT);
	m_armySprite->setFrame(1);

	m_markedIndicator.setRadius((float)ARMY_TILESIZE / 2 - 5);
	m_markedIndicator.setPointCount(40);
	
	m_powerBar.setSize(Vector2f(ARMY_POWERBAR_THICKNESS, static_cast<float>(64 * units->getUnitgroupStrength())));
	m_powerBar.setFillColor(MyColors.player[units->player_ID]);
	
	m_pBarBg.setSize(Vector2f(ARMY_POWERBAR_THICKNESS, ARMY_TILESIZE));
	Color c = MyColors.player[units->player_ID];
	c.a = 100;
	m_pBarBg.setFillColor(c);


	m_markedIndicator.setFillColor(MyColors.Transparent);

	PositionGraphics();
}

Army::~Army()
{
	delete m_armySprite;
	delete m_texture;
}

void Army::PositionGraphics()
{
	Vector2f pos;
	if(!m_animating)
		pos = (Vector2f)m_position;
	else
		pos = Vector2f(m_dimensions.left, m_dimensions.top);

	pos = pos * (float)ARMY_TILESIZE - (Vector2f)m_mapViewOffset;
	m_armySprite->setPosition(pos.x - 2, pos.y);

	m_markedIndicator.setPosition(pos.x + 5 , pos.y + 5);
	m_pBarBg.setPosition(pos);
	m_powerBar.setPosition(pos.x, pos.y + 64 - m_powerBar.getSize().y);
	

	//set the position of graphic objects
}

//IDrawable
void Army::draw(sf::RenderWindow* rw)
{
	if(!m_isVisible)
		return;
	if(m_inCity)
	{
		if(m_marked || m_mouseOver) 
			rw->draw(m_markedIndicator);
		rw->draw(*m_armySprite);
	}
	rw->draw(m_powerBar);
	rw->draw(m_pBarBg);

	
}

//IClickable
bool Army::MouseMoved(sf::Vector2i & mouse)
{
	if(!m_isVisible)
		return false;

	if( mouse.x == units->pos.x && mouse.y == units->pos.y)
	{
		m_mouseOver = true;
		if(!m_marked)
		{
			Color tmp = m_playerColor;
			tmp.a = 100;
			m_markedIndicator.setFillColor(tmp);
		}
	}
	else	
	{
		m_mouseOver = false;
	}
	return m_mouseOver;
}

bool Army::PressedLeft()
{
	if(!m_isVisible)
		return false;
	if(m_mouseOver)
	{
		m_marked = true;
		m_markedIndicator.setFillColor(m_playerColor);
		return true;
	}
	else
	{
		m_marked = false;
		return false;
	}
		
}

bool Army::PressedRight(){ return false; }
bool Army::ReleasedRight(){ return false; }
bool Army::ReleasedLeft(){ return false; }



void Army::animationTick()
{
	if(m_animation > 0)
	{
		m_animation --;
		float ratio = static_cast<float>(m_animation) / ARMY_ANIMATIONSTEPS;	
		Vector2f currentPos = m_a_oldPos * ratio + m_a_targetPos * (1 - ratio);
		m_dimensions.left = currentPos.x;
		m_dimensions.top = currentPos.y;

		PositionGraphics();

		if(m_animation == 0)
			m_animating = false;
	}
}

Vector2i Army::getPosition()
{
	return m_position;
}

void Army::setPosition(Vector2i pos)
{
	move(pos - m_position);
}

void Army::move(Vector2i delta)
{
	m_dimensions.left = static_cast<float>(m_Tilesize.x * (delta.x + m_position.x) -  m_mapViewOffset.x);
	m_dimensions.top = static_cast<float>(m_Tilesize.y * (delta.y + m_position.y) -  m_mapViewOffset.y);
	m_position += delta;

	PositionGraphics();
}


bool Army::animatedMove(Vector2i target)
{
	if(m_animating)	//if animation is running return false;
		return false;

	m_animation = ARMY_ANIMATIONSTEPS + 1;
	m_animating = true;
	m_a_oldPos = Vector2f(m_dimensions.left,m_dimensions.top);
	m_a_targetPos = Vector2f( static_cast<float>(target.x * m_Tilesize.x),
							static_cast<float>(target.y * m_Tilesize.y));


	return true;
}

ingameObjectType Army::getType()
{
	return ingameObjectType::ARMY;
}

Army* Army::split(int selection, std::vector<UnitGroup> & newUnits)
{
	//UnitGroup* p = new UnitGroup(;
	return NULL;
}


void Army::onMapMove(Rect<int> mapv)
{
	m_mapViewOffset = Vector2i(mapv.left, mapv.top);
	PositionGraphics();
}

int Army::getPlayerID()
{
	return this->m_playerID;
}

void Army::setPower(float power)
{
	m_powerBar.setSize(Vector2f(ARMY_POWERBAR_THICKNESS, ARMY_TILESIZE * power));
	PositionGraphics();
}
