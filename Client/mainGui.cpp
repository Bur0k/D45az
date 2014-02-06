#include "mainGui.h"


mainGui::mainGui()
{
	Image img;
	if(!img.loadFromFile("Data/Images/mainGui.png"))
		std::cout << "maingui.cpp : failed to load Data/Images/mainGui.png" << std::endl;

	background.t.loadFromImage(img);
	background.t.setSmooth(true);
	background.s.setTexture(& background.t);
	background.s.setSize((Vector2f)img.getSize());

	select_army = new StandardButton(Vector2f(0,0),Vector2f(100,30),std::string("Army"), MAINGUI_SELECTARMY,true);
	select_army->setIsEnabled(false);
	select_army->Attach(this);
	select_city = new StandardButton(Vector2f(0,0),Vector2f(100,30),std::string("City"), MAINGUI_SELECTCITY,true);
	select_city->setIsEnabled(false);
	select_city->Attach(this);
	army_mode[0] = new StandardButton(Vector2f(0,0),Vector2f(120,30),std::string("defensive"), MAINGUI_DEFENSIVE,false,false);
	army_mode[0]->Attach(this);
	army_mode[1] = new StandardButton(Vector2f(0,0),Vector2f(120,30),std::string("agressive"), MAINGUI_AGRESSIVE,false,false);
	army_mode[1]->Attach(this);
	army_mode[2] = new StandardButton(Vector2f(0,0),Vector2f(120,30),std::string("fast"), MAINGUI_HURRY,false,false);
	army_mode[2]->Attach(this);

	hidden = true;
	has_army = false;
	has_city = false;
	mouseOver = false;

	city = NULL;
	group = NULL;


	army_display = true;

	
}


mainGui::~mainGui()
{
	for(auto e : units)
		delete e;
	units.clear();

	delete select_army;
	delete select_city;

	for(int i = 0; i < 3; i++)
		delete army_mode[i];
}

void mainGui::positionGraphics()
{
	float y_origin = y_offset - ((hidden)? MAINGUI_HEIGHT_HIDDEN : MAINGUI_HEIGHT);
	background.s.setPosition(0, y_origin);
	select_army->setPosition(50, y_origin + 25);
	select_city->setPosition(200, y_origin + 25);

	for(unsigned int i = 0; i < units.size(); i++)
		units[i]->setPosition(Vector2f(20 + 70 * (i % 8), (i < 7)? y_offset - 186 : y_offset - 92));

}

void mainGui::updateMgui(City* city, UnitGroup* army)
{
	if(city != NULL)
	{
		this->city = city;
		has_city = true;
	}
	if(army != NULL)
	{
		this->group = army;
		has_army = true;
	}

	
	select_city->setIsEnabled(has_city);
	if(!has_city)
		select_city->unLock();
	select_army->setIsEnabled(has_army);
	if(!has_army)
		select_army->unLock();

	bool oldhidden = hidden;

	if(!has_city && !has_army)
		hidden = true;
	else 
		hidden = false;

	if(hidden != oldhidden)
		positionGraphics();
}

bool mainGui::MouseMoved(sf::Vector2i & mouse)
{
	bool retvalue;
	retvalue |= select_army->MouseMoved(mouse);
	retvalue |= select_city->MouseMoved(mouse);

	if(army_display && has_army)
	{
		for(int i = 0; i < 3; i++)
			retvalue |= army_mode[i]->MouseMoved(mouse);
		for(Unit* u : units)
			retvalue |= u->MouseMoved(mouse);
	}
	return retvalue;
}

bool mainGui::PressedLeft()
{
	bool retvalue;
	
	retvalue |= select_army->PressedLeft();
	retvalue |= select_city->PressedLeft();

	if(army_display && has_army)
	{
		for(int i = 0; i < 3; i++)
			retvalue |= army_mode[i]->PressedLeft();
		for(Unit* u : units)
			retvalue |= u->PressedLeft();
	}
	return retvalue;
}

bool mainGui::ReleasedLeft()
{
	bool retvalue;
	retvalue |= select_army->ReleasedLeft();
	retvalue |= select_city->ReleasedLeft();

	if(army_display && has_army)
	{
		for(int i = 0; i < 3; i++)
			retvalue |= army_mode[i]->ReleasedLeft();
		for(Unit* u : units)
			retvalue |= u->ReleasedLeft();
	}
	return retvalue;
}

void mainGui::onButtonClick(int id)
{
	switch (id)
	{
	case MAINGUI_SELECTARMY:
		if(has_army && select_army->getIsPressed())
		{
			hidden = false;
			positionGraphics();
			
			displayArmy();
			
			select_city->unLock();
		}
		break;

	case MAINGUI_SELECTCITY:
		if(has_city && select_city->getIsPressed())
		{
			hidden = false;
			positionGraphics();
			select_army->unLock();
		}
		break;

	case MAINGUI_DEFENSIVE:
		break;

	case MAINGUI_AGRESSIVE:
		break;

	case MAINGUI_HURRY:
		break;

	default:
		break;
	}



}

bool mainGui::PressedRight(){  return false; }
bool mainGui::ReleasedRight(){ return false; }


void mainGui::draw(sf::RenderWindow* rw)
{
	rw->draw(background.s);
	select_army->draw(rw);
	select_city->draw(rw);
	
	
	if(army_display && has_army)
	{
		for(Unit* u : units)
			u->draw(rw);
	
		for(int i = 0; i < 3; i++)
			rw->draw(*army_mode[i]);
	}
}

void mainGui::onResize(sf::Vector2u size)
{
	y_offset = static_cast<float>(size.y);
	positionGraphics();
}

void mainGui::animationTick()
{
	select_army->animationTick();
	select_city->animationTick();
	for(int i = 0; i < 3; i++)
		army_mode[i]->animationTick();
}

void mainGui::displayArmy()
{
	for(Unit* u : units)
		delete u;
	units.clear();

	for(int i = 0; i < 16; i++)
		if(group->units[i].count > 0)
			units.push_back(new Unit(Vector2f(0,0),group->units[i].type,group->units[i].count));

	positionGraphics();
}

