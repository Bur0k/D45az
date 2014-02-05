#include "Chat.h"


Chat::Chat():
	displayedChatLines(sf::Vector2f(0,300),sf::Vector2f(400,200),"",14),
	toSend(400,"Chat here",sf::Vector2f(0,500),true,0),
	b(sf::Vector2f(400,500), sf::Vector2f(26,toSend.getSize().y), "<", 0, false, false)
{
	displayedChatLines.setBackgroundColor(MyColors.Transparent);
	toSend.Attach(this);
	s = new Slider(false,sf::Vector2f(20,200),1.0,sf::Vector2f(405,300),0);
	s->Attach(this);

	c = Client::get();
	c->addToNewMessageCallback(this);

	b.Attach(this);

	rs.setFillColor(MyColors.WhiteTransparent);
	rs.setPosition(0,300);
	rs.setSize(sf::Vector2f(426,200));
	
	active=true;
	onButtonClick(0);//Set to false and Position
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
		rw->draw(rs);
		displayedChatLines.draw(rw);
		toSend.draw(rw);
		s->draw(rw);
	}
	b.draw(rw);
}

void Chat::onButtonClick(int id)
{
	active=!active;
	if(active)
	{
		b.setPosition(400,500);
		b.setText("<");
		b.m_color = MyColors.White;
		b.updateVisuals();
	}
	else
	{
		b.setPosition(0,500);
		b.setText(">");
	}
}

bool Chat::MouseMoved(sf::Vector2i & v)
{
	if(active)
	{
		s->MouseMoved(v);
		toSend.MouseMoved(v);
	}
	b.MouseMoved(v);
	return false;
}

bool Chat::PressedRight()
{
	return false;
}

bool Chat::PressedLeft()
{
	if(active)
	{
		s->PressedLeft();
		toSend.PressedLeft();
	}
	b.PressedLeft();
	return false;
}

bool Chat::ReleasedRight()
{
	return false;
}

bool Chat::ReleasedLeft()
{
	if(active)
	{
		s->ReleasedLeft();
		toSend.ReleasedLeft();
	}
	b.ReleasedLeft();
	return false;
}
	
void Chat::animationTick()
{
	if(active)
	{
		toSend.animationTick();
	}
	b.animationTick();
}
	
void Chat::onKeyDown(sf::Event e)
{
	if(active)
	{
		toSend.onKeyDown(e);
	}
	else
	{
	}
}

void Chat::onKeyUp(sf::Event e)
{
	if(active)
	{
		toSend.onKeyUp(e);
	}
	else
	{
	}
}

void Chat::onTextInput(std::string s)
{
	if(active)
	{
	if(toSend.getText().length()<40)
		toSend.onTextInput(s);
	}
	else
	{
	}
}

void Chat::onSliderValueChange(int ID, double position)
{
	if(active)
	{
		updateDisplayedChatLinesMutex.lock();
		updateDisplayedChatLines();
		updateDisplayedChatLinesMutex.unlock();
	}
	else
	{
	}
}
void Chat::onSliderReleased(int ID, double position)
{

}

void Chat::update(double elapsedMs)
{
}

void Chat::onTextBoxSend(int ID, std::string s)
{
	if(active)
	{
		c->write(0x1000,code(s));
		toSend.clear();
	}
	else
	{
	}
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
			if(!active)
			{
				b.m_color = MyColors.Chartreuse;
				b.animationTick();
			}
		}break;
	}
}

void Chat::processNetworkError(int id, std::string msg)
{

}
