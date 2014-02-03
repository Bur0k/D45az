#include "Chat.h"


Chat::Chat():
	displayedChatLines(sf::Vector2f(0,300),sf::Vector2f(400,200),"",14),
	toSend(400,"Chat here",sf::Vector2f(0,500),true,0)
{
	s = new Slider(false,sf::Vector2f(14,200),1.0,sf::Vector2f(405,300),0);
	s->Attach(this);

	c = Client::get();
	c->addToNewMessageCallback(this);
	active=true;

	for(int i=0;i<5;i++)
		chatLines.push_front(to_string(i)+"te Zeile. Wuhuuuuuuuu");
	updateDisplayedChatLines();
}

Chat::~Chat()
{
	c->deleteFromNewMessageCallback(this);
	delete s;
}

void Chat::draw(sf::RenderWindow* rw)
{
	if(active)
	{
		displayedChatLines.draw(rw);
		toSend.draw(rw);
		s->draw(rw);
	}
	else
	{
	}
}

bool Chat::MouseMoved(sf::Vector2i & v)
{
	s->MouseMoved(v);
	return toSend.MouseMoved(v);
}

bool Chat::PressedRight()
{
	return false;
}

bool Chat::PressedLeft()
{
	s->PressedLeft();
	toSend.PressedLeft();
	return false;
}

bool Chat::ReleasedRight()
{
	return false;
}

bool Chat::ReleasedLeft()
{
	s->ReleasedLeft();
	toSend.ReleasedLeft();
	return false;
}
	
void Chat::animationTick()
{
	toSend.animationTick();
}
	
void Chat::onKeyDown(sf::Event e)
{
	toSend.onKeyDown(e);
}

void Chat::onKeyUp(sf::Event e)
{
	toSend.onKeyUp(e);
}

void Chat::onTextInput(std::string s)
{
	if(toSend.getText().length()<40)
		toSend.onTextInput(s);
}

void Chat::onSliderValueChange(int ID, double position)
{/*
	static double lastPos = 0.0;
	if(lastPos == position)
		return;
	lastPos = position;*/
	updateDisplayedChatLinesMutex.lock();
	updateDisplayedChatLines();
	updateDisplayedChatLinesMutex.unlock();
}
void Chat::onSliderReleased(int ID, double position)
{

}

void Chat::update(double elapsedMs)
{
}

void Chat::onTextBoxSend(int ID, std::string s)
{
	c->write(0x1000,code(s));
	toSend.clear();
}

void Chat::updateDisplayedChatLines()
{	
	const int maxLines = 11;
	int startIndex = static_cast<int>((1.0 - s->getValue()) * (chatLines.size()-1) + 0.5);
	
	static string oldChatBoxString = "";
	string newChatBoxString;

	for(int i=startIndex;i<startIndex+maxLines;i++)
	{
		if(static_cast<unsigned int>(i) >= chatLines.size())
			newChatBoxString.insert(0,"\n");
		else
			newChatBoxString.insert(0,chatLines[i]+"\n");
	}
	if(oldChatBoxString == newChatBoxString)
		return;
	oldChatBoxString=newChatBoxString;
	displayedChatLines.setText(newChatBoxString,sf::Vector2f(400,200));
}


void Chat::processNewMessage(short id,vector<char> data)
{
	switch(id)
	{
	case 0x1001:
		{
			updateDisplayedChatLinesMutex.lock();
			chatLines.push_front(decodeString(data,0,data.size()));
			if(chatLines.size() > 30)
				chatLines.pop_back();
			updateDisplayedChatLines();
			updateDisplayedChatLinesMutex.unlock();
		}break;
	}
}

void Chat::processNetworkError(int id, std::string msg)
{

}