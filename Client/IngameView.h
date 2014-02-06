#ifndef INGAMEVIEW_H
#define INGAMEVIEW_H

#include <vector>
#include <SFML\Graphics.hpp>
#include "IView.h"
#include "StandardButton.h"
#include "Slider.h"
#include "Textblock.h"
#include "Textbox.h"
#include "Unit.h"
#include "Map.h"
#include "Statusbar.h"
#include "CommitButton.h"
#include "Army.h"
#include "LogicData.h"
#include "Chat.h"
#include "mainGui.h"
#include "MusikSampler.h"

//#define INGAMEVIEW_MAX_MAPSPEED  20
//#define INGAMEVIEW_MOUSEOVER_RECT_BORDER 2
//
//#define INGAMEVIEW_SCROLLEXESS 150
//
//#define INGAMEVIEW_LIGHT_SIGHT 8
//#define INGAMEVIEW_HEAVY_SIGHT 8
//#define INGAMEVIEW_RANGED_SIGHT 8
//#define INGAMEVIEW_ARTILLERY_SIGHT 8

static const float INGAMEVIEW_MAX_MAPSPEED = 20.0f;
static const float INGAMEVIEW_MOUSEOVER_RECT_BORDER = 2.0f;

static const int INGAMEVIEW_SCROLLEXESS = 150;

static const int INGAMEVIEW_LIGHT_SIGHT = 8;
static const int INGAMEVIEW_HEAVY_SIGHT = 8;
static const int INGAMEVIEW_RANGED_SIGHT = 8;
static const int INGAMEVIEW_ARTILLERY_SIGHT = 8;


enum class IngameViewButtonId{
	COMMIT = 0,
};

enum class InagameViewPhases{
	YOURTURN,			//moving units and building is allowed
	WAITFORPLAYERS,		//wait till all players have finished their 
	WATCHRESULTS,		//watch results of the last turn
	GAMEOVER			//game has ended no further information from the server is required and the fog of war will be turned off
};

class turn
{
public:
	sf::Vector2i pos;
	bool valid;
	turn(){valid=true;};
	turn(sf::Vector2i Pos){pos=Pos;valid=true;}
};

struct buildOrders
{

};



class IngameView : 
	public IView, public IButtonfunction, public ISliderFunction, public ITextBoxFunction
{
private:

	Client* c;

	//path drawing
	bool m_turnOnPathDraw;
	short m_maxLen;
	bool m_is_turn_valid;
	std::vector<turn> currentTurn;//Von hier rauslesen. Wenn ein neuer Zug gemacht werden soll, einfach currentTurn.clear().
	std::vector<turn> mouseOverTurn;
	RectangleShape rsTurn;
	MapLayer* collisionLayer;

	//vector of all moves the player made
	std::vector<std::vector<sf::Vector2i>> army_moves;
	//vector of all units built;
	
	//vector of all owned armys
	std::vector<Army*> m_owned_armys;
	std::vector<Army*> m_enemy_armys;


	//Fog of war
	bool turnOnFogOfWar;
	bool updateNewFogOfWar;
	std::vector<std::vector<bool>> toDraw;
	void updateFogOfWar();

	//CHAT
	Chat chat;
	
	//Main Gui
	mainGui mainGuiOBJECT;

	//debug

	Unit* u, * u1;

	//debug off


	CommitButton* m_commitB;
	MusikSampler* m_pMS; 

	//Visible STUFF
	Statusbar* m_SBar;	
	Map m_map;
	IntRect m_mapView;
	Vector2i m_mapSize;
	Vector2i m_tileSize;
	Vector2i m_mapTileSize;

	//logic
	LogicData m_GameData;


	Vector2u m_screensize;
	//pixels
	Vector2i m_mapTotalSize;

	

	//user points at 
	Vector2i m_pointAt;
	Vector2i m_activeAt;

	//scrolling the map
	Vector2i m_scrolldir;
	Vector2f m_scrollspeed;

	//vectors for handling the events
	DrawVect m_DrawV;
	AnimateVect m_AnimateV;
	ClickVect m_ClickV;
	KeyInputVect m_KeyV;

	Views m_nextView;

	//gameStatus
	InagameViewPhases m_phase;
	
	RectangleShape m_mapMouseOver;

	//rectangles behind cities in playercolor
	vector<sf::RectangleShape> m_RectangleCityShapes;

public:
	IngameView(Vector2u & screensize, StatusBarFunctions* SBar_Function, InagameViewPhases startphase);
	~IngameView();

	//param x : -1, 0, +1
	//param y : same
	void setScrollDirection(int x, int y);


	////IMPLEMENTING IView/////
	//IDrawable
	void draw(sf::RenderWindow* rw);

	//IClickable
	bool MouseMoved(sf::Vector2i &);
	bool PressedRight();
	bool PressedLeft();
	bool ReleasedRight();
	bool ReleasedLeft();
	
	void animationTick(); 
	//IKey
	void onKeyDown(sf::Event);
	void onKeyUp(sf::Event);
	void onTextInput(std::string s);

	void onResize(sf::Vector2u &);
	void update(double elapsedMs);

	Views getType();
	Views nextState();
	//IClickable
	void onButtonClick(int);
	void onSliderValueChange(int ID, double position);
	void onSliderReleased(int ID, double position);
	void onTextBoxSend(int ID, std::string s);

	// Turn committed!! //

	void commitMessage();
	void commitArmyStrategy();
	void commitMoves();
	void commitCityActions();

	/////IMPLEMENTING IView end/////

private:
	//gets called if next phase is required
	void nextPhase();
	void moveMap();
	void displayCityInfo(City*);
	void displayArmyInfo(UnitGroup*);
	void drawPath();
	//saves path to army at path[0]
	void addPathToArmy();
	//loads path from army at pos
	void loadPath(Vector2i pos);
	void drawMouseOverPath();
	//returns true if object is not covered by fog of war
	bool isVisible(Vector2i pos);

	void loadGamestate();


	void fogOfWardraw(RenderWindow* rw);
	//renders the path on screen
	void pathDraw(RenderWindow* rw);

	bool isInCity(UnitGroup*);

	int getRemainingMovementPoints(UnitGroup*);

};





#endif //INGAMEVIEW_H