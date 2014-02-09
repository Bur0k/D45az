#ifndef MAINGUI_H
#define MAINGUI_H

#include <iostream>
#include <vector>
#include "graphic_globals.h"
#include "IClickable.h"
#include "StandardButton.h"
#include "Unit.h"
#include "UnitGroup.h"
#include "City.h"
#include "IDrawable.h"
#include "Textblock.h"
#include "Statusbar.h"

//#define MAINGUI_SELECTARMY 0
//#define MAINGUI_SELECTCITY 1
//#define MAINGUI_DEFENSIVE 2
//#define MAINGUI_AGRESSIVE 3
//#define MAINGUI_HURRY 4
//#define MAINGUI_HEIGHT 250
//#define MAINGUI_HEIGHT_HIDDEN 70 

static const int MAINGUI_SELECTARMY = 0;
static const int MAINGUI_SELECTCITY = 1;
static const int MAINGUI_DEFENSIVE = 2;
static const int MAINGUI_AGRESSIVE = 3;
static const int MAINGUI_HURRY = 4;
static const int MAINGUI_HEIGHT = 250;
static const int MAINGUI_HEIGHT_HIDDEN = 70;
static const int MAINGUI_UNDO_MOVE = 22; 
const int maingui_light = 5;
const int maingui_heavy = 6;
const int maingui_longrange = 7;
const int maingui_artillery= 8;
const int maingui_city= 9;

const int lightPrice = 10;
const int heavyPrice = 25;
const int longrangePrice = 40;
const int artilleryPrice = 55;
const int cityUpgrade = 50;

class ImainGuiFunc
{
public:
	virtual void deleteMoves(UnitGroup*, int length)=0;
};



class mainGui
	: public IClickable, public IButtonfunction, public IDrawable, public IAnimatable
{
private:
	

	SpriteTex background;
	std::vector<Unit*> units;
	StandardButton* select_army;
	StandardButton* select_city;
	StandardButton* army_mode[3];
	StandardButton* deleteMove;

	
	

	void positionGraphics();

	bool mouseOver;
	
	bool hidden;

	void displayArmy();
	void displayCity();
	Textblock cityIncome;
	Textblock cityLevel;
	std::vector<Unit*> cityUnits;
	std::vector<StandardButton*> cityUnityBuy;
	struct CityActions
	{
		Vector2i pos;
		bool updating;
		int numOfProducingUnit;
		UnitTypes ProducedUnit;
	};
	int currentCityActionsIndex;
	std::vector<CityActions> updateInfo;
	
	void resetModeButtons();

public:
	ImainGuiFunc* deleteMoveFunction;
	Statusbar* statusbar;
	std::vector<unsigned char> getCityActionData();
	float y_offset;

	bool has_army;
	bool has_city;
	bool army_display;
	bool city_display;
	

	mainGui();
	~mainGui();

	void updateMgui(City * c, UnitGroup*);
	void onResize(sf::Vector2u);
	City* city;
	UnitGroup* group;

	//iclickablese
	bool MouseMoved(sf::Vector2i &);
	bool PressedRight();
	bool PressedLeft();
	bool ReleasedRight();
	bool ReleasedLeft();

	//ibuttonfunction
	void onButtonClick(int);
	//idrawable
	void draw(sf::RenderWindow* rw);
	//ianimatable
	void animationTick();

	void  Clear();

};



#endif //MAINGUI_H