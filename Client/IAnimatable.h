#ifndef IANIMATABLE_H
#define IANIMATABLE_H

#include <vector>

class IAnimatable
{
public:
	virtual void animationTick()=0;
};

typedef std::vector<IAnimatable*> AnimateVect;

#endif
