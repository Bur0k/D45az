#ifndef SERVER_H
#define SERVER_H

#include <WinSock2.h>
#include <MSWSock.h>
#include <Windows.h>
#include <process.h>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <list>
#include "PlayerData.h"
#include <algorithm>

#include "NetworkParticipant.h"

using namespace std;

//Lowbyte zuerst
std::vector<unsigned char> code(short s);
std::vector<unsigned char> code(int i);
std::vector<unsigned char> code(const std::string s);
short decodeShort(const std::vector<unsigned char>& v, int from);
int decodeInt(const std::vector<unsigned char>& v, int from);
std::string decodeString(const std::vector<unsigned char>& v, int from, int len);

class Server
{
	typedef enum _OPERATION_INFO_
	{
		OP_NULL,
		OP_ACCEPT,
		OP_READ,
		OP_WRITE
	}OPERATIONINFO;

	typedef struct _PER_HANDLE_DATA_
	{
	public:
		_PER_HANDLE_DATA_()
		{
			clean();
		}
		~_PER_HANDLE_DATA_()
		{
			clean();
		}
	protected:
		void clean()
		{
			sock = INVALID_SOCKET;
			memset(&addr, 0, sizeof(addr));
			addr.sin_addr.S_un.S_addr = INADDR_ANY;
			addr.sin_port = htons(0);
			addr.sin_family = AF_INET;
		}
	public:	
		SOCKET sock;
		SOCKADDR_IN addr;
	}PERHANDLEDATA;

	typedef struct _PER_IO_DTATA_
	{
	public: 
		_PER_IO_DTATA_()
		{
			clean();
		}
		~_PER_IO_DTATA_()
		{
			clean();
		}
		void clean()
		{
			ZeroMemory(&ol, sizeof(ol));
			memset(buf, 0, sizeof(buf));
			sAccept = INVALID_SOCKET;
			sListen = INVALID_SOCKET;
			wsaBuf.buf = buf;
			wsaBuf.len = 1024;
			opType =  OP_NULL;
			currPos = 0;
			nextMsgSize = 0;
		}
	public:
		WSAOVERLAPPED ol;
		SOCKET sAccept; // Only valid with AcceptEx
		SOCKET sListen; // Only valid with AcceptEx
		WSABUF wsaBuf;
		char buf[1024];
		OPERATIONINFO opType;

		short currPos;
		short nextMsgSize;
		vector<unsigned char> buffer_;
	}PERIODATA;

	HANDLE hThread[4];
	PERIODATA* pAcceptData[100];
	int g_nThread;
	BOOL g_bExitThread;
	LPFN_ACCEPTEX lpfnAcceptEx;
	LPFN_GETACCEPTEXSOCKADDRS lpfnGetAcceptExSockAddrs;
	GUID GuidAcceptEx;
	GUID GuidGetAcceptExSockAddrs;

	unsigned static __stdcall ThreadProc(LPVOID lParam);
	BOOL PostAccept(PERIODATA* pIoData);

	SOCKET sListen;
	HANDLE hIOCP;


	void sendError(SOCKET s,int errCode,string errMessage);
	void sendNewMessage(SOCKET s, short id,vector<unsigned char> data);
	vector<NetworkParticipant*> errorCallback;
	vector<NetworkParticipant*> newMessageCallback;
	mutex newMessageCallbackMutex;
	mutex errorCallbackMutex;

	class writeData
	{
	public:
		SOCKET s;
		vector<unsigned char> data;
		writeData(SOCKET S,vector<unsigned char> Data)
		{
			s=S;
			data=Data;
		}
		writeData()
		{
		}
	};
	thread* writeThread;
	list<writeData> toWrite;
	mutex toWriteMutex;
	
	struct error
	{
		SOCKET s;
		short errCode;
		string errMessage;
		error(SOCKET S,short ErrCode,string ErrMessage):s(S),errCode(ErrCode),errMessage(ErrMessage){}
	};
	vector<error> errorQueue;
	mutex errorQueueMutex;
	vector<NetworkParticipant*> addErrorCallbackList;
	mutex addErrorCallbackMutex;
	vector<NetworkParticipant*> deleteErrorCallbackList;
	mutex deleteErrorCallbackMutex;
	thread* addDeleteProcessErrorCallback;


	struct newMessage
	{
		SOCKET s;
		short id;
		std::vector<unsigned char> data;
		newMessage(SOCKET S,short ID,std::vector<unsigned char> Data):s(S),id(ID),data(Data){}
	};
	vector<newMessage> newMessageQueue;
	mutex newMessageQueueMutex;
	vector<NetworkParticipant*> addNewMessageCallbackList;
	mutex addNewMessageCallbackMutex;
	vector<NetworkParticipant*> deleteNewMessageCallbackList;
	mutex deleteNewMessageCallbackMutex;
	thread* addDeleteProcessNewMessageCallback;
	

	bool running;
	static Server* self;
	Server();
public:

	static Server* get()
	{
		return self;
	}

	~Server();

	std::vector<PlayerData> connectedPlayers;

	void startListening();
	void write(SOCKET s,short id,vector<unsigned char> data);

	void addToNewMessageCallback(NetworkParticipant* np);
	void deleteFromNewMessageCallback(NetworkParticipant* np);
	void addToErrorCallback(NetworkParticipant* np);
	void deleteFromErrorCallback(NetworkParticipant* np);
};
#endif