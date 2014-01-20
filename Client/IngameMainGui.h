#ifndef INGAMEMAINGUY_H
#define INGAMEMAINGUY_H

#include <SFML\Graphics.hpp>
#include "IView.h"
#include "StandardButton.h"
#include "Slider.h"
#include "Textblock.h"
#include "Textbox.h"

using namespace sf;

enum class GuiModes{EMPTY, CITY, ARMY};

class IngameMainGuy	: 
	public IView, public IButtonfunction, public ISliderFunction, public ITextBoxFunction
{
private:

	
	SpriteTex m_Background;

	GuiModes mode;

	//0-3 images for purchase mode rest for army mode
	SpriteTex* Unit_images;
	Text* m_city_purchaseText;
	StandardButton* m_city_buyUnitButtons;

	

	DrawVect m_DrawV;
	AnimateVect m_AnimateV;
	ClickVect m_ClickV;
	KeyInputVect m_KeyV;


public:
	IngameMainGuy(Vector2u & screensize);
	~IngameMainGuy();


	void draw(sf::RenderWindow* rw);

	bool MouseMoved(sf::Vector2i &);
	bool PressedRight();
	bool PressedLeft();
	bool ReleasedRight();
	bool ReleasedLeft();
	
	void animationTick(); 
	
	void onKeyDown(sf::Event);
	void onKeyUp(sf::Event);
	void onTextInput(std::string s);

	void onResize(sf::Vector2u &);
	

	void onButtonClick(int);
	void onSliderValueChange(int ID, double position);
	void onSliderReleased(int ID, double position);
	void onTextBoxSend(int ID, std::string s);
};

#endif //INGAMEMAINGUY_H