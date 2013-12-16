#ifndef CLIENT_H
#define Server_H

#include <WinSock2.h>
#include <MSWSock.h>
#include <Windows.h>
#include <process.h>
#include <string>
#include <list>
#include <vector>
#include <thread>
#include <mutex>
#include "ClientHandler.h"

using namespace std;

class Server
{
	/*long rc;
	SOCKET acceptSocket;
	SOCKADDR_IN addr;


	void sendError(ClientHandler* ch,int errCode,string errMessage);

	thread* acceptThread;
	bool runAccept;

	vector<ClientHandler*> clientHandler;
	public:
	Server();
	~Server();

	void startListening();
	vector<void (*)(ClientHandler* ch,int errCode,string errMessage)> errorCallback;
	vector<void (*)(ClientHandler* ch,short id,vector<char> data)> newMessageCallback;*/

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
	}PERHANDLEDATA, *PPERHANDLEDATA;

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
		}
	public:
		WSAOVERLAPPED ol;
		SOCKET sAccept; // Only valid with AcceptEx
		SOCKET sListen; // Only valid with AcceptEx
		WSABUF wsaBuf;
		char buf[1024];
		OPERATIONINFO opType;
	}PERIODATA, *PPERIODATA;

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


public:
	Server();
	~Server();

	static Server* self;

	void startListening();
};
#endif