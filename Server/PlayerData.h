#ifndef _PLAYERDATA_
#define _PLAYERDATA_

#include <WinSock2.h>
#include <string>
#include <concurrent_vector.h>
#include <mutex>

struct PlayerData
{
public:
	SOCKET s;
	std::string Name;
};

concurrency::concurrent_vector<PlayerData> connectedPlayers;

#endif