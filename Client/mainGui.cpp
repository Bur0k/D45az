#include "mainGui.h"


mainGui::mainGui():
	cityLevel(sf::Vector2f(0,0),sf::Vector2f(0,0),"",18),
	cityIncome(sf::Vector2f(0,0),sf::Vector2f(0,0),"",18)
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
	city_display = false;

	cityLevel.setBackgroundColor(MyColors.Transparent);
	cityIncome.setBackgroundColor(MyColors.Transparent);
	cityUnits.push_back(new Unit(sf::Vector2f(0,0),UnitTypes::LIGHT,0));
	cityUnits.push_back(new Unit(sf::Vector2f(0,0),UnitTypes::HEAVY,0));
	cityUnits.push_back(new Unit(sf::Vector2f(0,0),UnitTypes::LONGRANGE,0));
	cityUnits.push_back(new Unit(sf::Vector2f(0,0),UnitTypes::ARTILLERY,0));
	cityUnityBuy.push_back(new StandardButton(Vector2f(0,0),Vector2f(60,30),std::string("Light"), maingui_light,false,false));
	cityUnityBuy.push_back(new StandardButton(Vector2f(0,0),Vector2f(60,30),std::string("Heavy"), maingui_heavy,false,false));
	cityUnityBuy.push_back(new StandardButton(Vector2f(0,0),Vector2f(60,30),std::string("Longrange"), maingui_longrange,false,false));
	cityUnityBuy.push_back(new StandardButton(Vector2f(0,0),Vector2f(60,30),std::string("Artillery"), maingui_artillery,false,false));

	for(auto it : cityUnityBuy)
		it->Attach(this);
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

	for(auto it : cityUnits)
		delete it;
	for(auto it : cityUnityBuy)
		delete it;
}

void mainGui::positionGraphics()
{
	float y_origin = y_offset - ((hidden)? MAINGUI_HEIGHT_HIDDEN : MAINGUI_HEIGHT);
	background.s.setPosition(0, y_origin);
	select_army->setPosition(50, y_origin + 25);
	select_city->setPosition(200, y_origin + 25);

	for(unsigned int i = 0; i < units.size(); i++)
		units[i]->setPosition(Vector2f(20 + 70 * (i % 8), (i < 7)? y_offset - 186 : y_offset - 92));

	for(int i = 0; i < 3; i++)
		army_mode[i]->setPosition(Vector2f(600,y_origin + i * 40));
	
	
	cityLevel.setPos(sf::Vector2f(30,y_origin+75));
	cityIncome.setPos(sf::Vector2f(30,y_origin+100));

	int startX = 150;
	
	for(unsigned int i=0;i<cityUnits.size();i++)
	{
		cityUnits[i]->setPosition(sf::Vector2f(startX,y_origin+75));
		cityUnityBuy[i]->setPosition(sf::Vector2f(startX,y_origin+175));
		startX+=75;
	}
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
	if(city_display)
		for(auto it : cityUnityBuy)
			it->MouseMoved(mouse);
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
	if(city_display)
		for(auto it : cityUnityBuy)
			it->PressedLeft();
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
	if(city_display)
		for(auto it : cityUnityBuy)
			it->ReleasedLeft();
	return retvalue;
}

void mainGui::onButtonClick(int id)
{
	switch (id)
	{
	case MAINGUI_SELECTARMY:
		if(has_army && select_army->getIsPressed())
		{
			army_display = true;
			hidden = city_display = false;
			positionGraphics();
			
			displayArmy();
			
			select_city->unLock();
		}
		break;

	case MAINGUI_SELECTCITY:
		if(has_city && select_city->getIsPressed())
		{
			army_display = hidden = false;
			city_display = true;
			positionGraphics();

			displayCity();

			select_army->unLock();
		}
		break;

	case MAINGUI_DEFENSIVE:
		break;

	case MAINGUI_AGRESSIVE:
		break;

	case MAINGUI_HURRY:
		break;

	case maingui_light:
		if(city->generatedIncome >= lightPrice)
		{
			city->generatedIncome -= lightPrice;
			cityUnityBuy[1]->setIsEnabled(false);
			cityUnityBuy[2]->setIsEnabled(false);
			cityUnityBuy[3]->setIsEnabled(false);
			cityUnits[0]->setNumberOfSoldiers(cityUnits[0]->getNumberOfSoldiers()+1);
			displayCity();
		}
		break;

	case maingui_heavy:
		if(city->generatedIncome >= heavyPrice)
		{
			city->generatedIncome -= heavyPrice;
			cityUnityBuy[0]->setIsEnabled(false);
			cityUnityBuy[2]->setIsEnabled(false);
			cityUnityBuy[3]->setIsEnabled(false);
			cityUnits[1]->setNumberOfSoldiers(cityUnits[1]->getNumberOfSoldiers()+1);
			displayCity();
		}
		break;

	case maingui_longrange:
		if(city->generatedIncome >= longrangePrice)
		{
			city->generatedIncome -= longrangePrice;
			cityUnityBuy[0]->setIsEnabled(false);
			cityUnityBuy[1]->setIsEnabled(false);
			cityUnityBuy[3]->setIsEnabled(false);
			cityUnits[2]->setNumberOfSoldiers(cityUnits[2]->getNumberOfSoldiers()+1);
			displayCity();
		}
		break;

	case maingui_artillery:
		if(city->generatedIncome >= artilleryPrice)
		{
			city->generatedIncome -= artilleryPrice;
			cityUnityBuy[0]->setIsEnabled(false);
			cityUnityBuy[1]->setIsEnabled(false);
			cityUnityBuy[2]->setIsEnabled(false);
			cityUnits[3]->setNumberOfSoldiers(cityUnits[3]->getNumberOfSoldiers()+1);
			displayCity();
		}
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
	else if(city_display)
	{
		cityIncome.draw(rw);
		cityLevel.draw(rw);
		for(auto it : cityUnits)
			it->draw(rw);
		for(auto it : cityUnityBuy)
			it->draw(rw);
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
	if(city_display)
		for(auto it : cityUnityBuy)
			it->animationTick();
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

void mainGui::displayCity()
{
	cityIncome.setText("Income: "+to_string(city->generatedIncome),sf::Vector2f(1000,1000));
	cityLevel.setText("Level: "+to_string(city->level),sf::Vector2f(1000,1000));

	positionGraphics();
}
