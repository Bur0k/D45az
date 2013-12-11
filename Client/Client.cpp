#include "Client.h"

Client::Client()
{
}

void Client::connectToServer(string ip, int port)
{
	s=socket(AF_INET,SOCK_STREAM,0);

	if(s==INVALID_SOCKET)
	{
		sendError(-1,"Socket could not be created: "+WSAGetLastError());
		return ;
	}

	sockaddr_in si;
	hostent *hostess_twinkies = gethostbyname(ip.c_str());

	si.sin_family = AF_INET;
	si.sin_port = htons(port);
	si.sin_addr = *((in_addr*) hostess_twinkies->h_addr);
	memset(&(si.sin_zero), 0, 8);
	if (connect(s, (sockaddr*) &si, sizeof(struct sockaddr)) == -1)
	{
		sendError(-2,"Socket could not connect: "+WSAGetLastError());
		return ;
	}
}


void Client::sendError(int errCode,string errMessage)
{
	for(unsigned int i=0;i<errorCallback.size();i++)
		errorCallback[i](errCode,errMessage);
}

void Client::sendNewMessage(short id,vector<char> data)
{
	for(unsigned int i=0;i<newMessageCallback.size();i++)
		newMessageCallback[i](id,data);
}

void Client::write(short id, vector<char>data)
{
	vector<char> toSend(data);
	short size = (short) data.size()+4;//2byte länge, 2byte id
	
	toSend.insert(toSend.begin(),(char)id);
	toSend.insert(toSend.begin(),(char)(id>>8));
	
	toSend.insert(toSend.begin(),(char)size);
	toSend.insert(toSend.begin(),(char)(size>>8));


}

void Client::beginRead()
{
}