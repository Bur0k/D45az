#ifndef NETWORKPARTICIPANT_H
#define NETWORKPARTICIPANT_H

#include <WinSock2.h>
#include <vector>
#include <string>

class NetworkParticipant
{
public:
	virtual void processNewMessage(short id,std::vector<unsigned char> data) = 0;
	virtual void processNetworkError(int errCode,std::string errMessage) = 0;
};


#endif