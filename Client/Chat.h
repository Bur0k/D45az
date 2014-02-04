#ifndef CHAT_H
#define CHAT_H

#include "Textblock.h"
#include <vector>
#include <deque>
#include "StandardButton.h"
#include "Slider.h"
#include "Textbox.h"
#include "NetworkParticipant.h"
#include "Client.h"
#include <mutex>

class Chat : public ISliderFunction, public ITextBoxFunction, public NetworkParticipant, public IButtonfunction
{
	TextBox toSend;
	Slider* s;
	RectangleShape rs;
	Button b;//Aussagekräftiger braucht man das nicht

	Textblock displayedChatLines;
	std::deque<std::string> chatLines;

	void updateDisplayedChatLines();
	Client* c;

	bool active;
	mutex updateDisplayedChatLinesMutex;
public:
	Chat();
	~Chat();

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

	void onSliderValueChange(int ID, double position);
	void onSliderReleased(int ID, double position);

	void update(double elapsedMs);

	void onTextBoxSend(int ID, std::string s);

	void processNewMessage(short id,vector<char> data);
	void processNetworkError(int id, std::string msg);

	void onButtonClick(int);
};


#endif //CHAT_H