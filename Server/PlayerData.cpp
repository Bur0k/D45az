#include "PlayerData.h"


template<class T>
std::vector<T> D45vector<T>::getCopy()
{
	return v;
}

template<class T>
int D45vector<T>::size()
{
	return v->size();
}

template<class T>
void D45vector<T>::push_back(T newData)
{
	m.lock();
	v.push_back(newData);
	m.unlock();
}

template<class T>
void D45vector<T>::erase(T toDelete)
{
	m.lock();
	for(std::vector<T>::iterator it=v.begin();it!=v.end();++it)
		if((*it)==toDelete)
		{
			v.erase(it);
			break;
		}
	m.unlock();
}