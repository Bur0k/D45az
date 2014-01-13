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
	SOCKET s;
	std::string Name;
};

template<class T>
class D45vector
{
private:
	std::vector<T> v;
	std::mutex m;
public:
	std::vector<T> getCopy();
	int size();
	void push_back(T newData);
	void erase(T toDelete);
};

#endif