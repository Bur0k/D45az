#ifndef NETWORKPARTICIPANT_H
#define NETWORKPARTICIPANT_H

#include <WinSock2.h>
#include <vector>
#include <string>

class NetworkParticipant
{
public:
	virtual void processNewMessage(SOCKET s,short id,std::vector<char> data) = 0;
	virtual void processNetworkError(SOCKET s,int errCode,std::string errMessage) = 0;
};


#endif