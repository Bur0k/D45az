#ifndef _PLAYERDATA_
#define _PLAYERDATA_

#include <WinSock2.h>
#include <string>
#include <concurrent_vector.h>
#include <mutex>
#include <vector>

struct PlayerData
{
public:
	std::string Name;
};

extern PlayerData playerData;

struct GameData
{
	std::vector<PlayerData> players;
	short playerlimit;
	PlayerData gameMaster;
	std::string name;
};


#endif
