#ifndef LOBBYENTRY_H
#define LOBBYENTRY_H

#include "Button.h"
#include "Textblock.h"
#include "graphic_globals.h"

class LobbyEntry : public Button
{
private:
	Rect<float> m_dimensions;

	Text m_name;
	Text m_number;
	int m_maxPlayers;
	int m_players;
	int m_ID;

public:
	LobbyEntry(Vector2f size, Vector2f pos, std::string name, int players, int maxplayers, int id);
	void move(Vector2f delta);
	
	void setName(std::string name);
	std::string getName();
	void setPlayers(int);
	int getPlayers();
	void setMaxPlayers(int);
	int getMaxPlayers();


	Vector2f getPosition();
	void setPosition(Vector2f pos);
	virtual void draw(RenderWindow* rw);
};

#endif //LOBBYENTRY_H