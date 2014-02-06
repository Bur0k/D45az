#ifndef LOBBYENTRY_H
#define LOBBYENTRY_H

#include "Button.h"
#include "Textblock.h"
#include "graphic_globals.h"

//#define LOBBYENTRYBORDER 10

static const float LOBBYENTRYBORDER = 10;

class LobbyEntry : public Button
{
private:
	Rect<float> m_dimensions;

	Text m_nameText;
	Text m_numberText;
	int m_maxPlayers;
	int m_players;
	int m_ID;

	void updatePlayers();
	LobbyEntry();
public:
	LobbyEntry(Vector2f size, Vector2f pos, std::string name, int players, int maxplayers, int id);
	void LEmove(Vector2f delta);
	
	void setName(std::string name);
	std::string getName();
	void setPlayers(int);
	int getPlayers();
	void setMaxPlayers(int);
	int getMaxPlayers();


	Vector2f getSize();
	Vector2f getPosition();
	void setPosition(Vector2f pos);
	virtual void draw(RenderWindow* rw);
	void setWidth(float);

	int getID(){return m_ID;}
};

#endif //LOBBYENTRY_H