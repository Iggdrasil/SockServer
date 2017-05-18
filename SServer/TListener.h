#pragma once
#include <WinSock2.h>
#define VERSION_MAJOR      2
#define VERSION_MINOR      0
#define MAX_LISTENING_SOCKETS    1024

typedef HRESULT(*EventHandler)(LPVOID lParam, DWORD dwIndex);

typedef struct tagLISTENSOCK
{
	SOCKET hSocket;
	LPWSAPROTOCOL_INFO ProtoInfo;
	//CClient* m_pClient;

}LISTENSOCK, *PLISTENSOCK;


class TListener
{
	DWORD port_;
	DWORD numAvailableProtocols;
	
	LPWSAPROTOCOL_INFO availableProtocols;
	HANDLE listeningEventObj[MAX_LISTENING_SOCKETS];

protected:
	DWORD numListeningSockets;
	LISTENSOCK listeningSockets[MAX_LISTENING_SOCKETS];

public:
	TListener();
	~TListener();

public:
	static void startListenThreadProc(LPVOID lpvParam);
	bool startServer(int port);
	static HRESULT OnRecive(SOCKET socket, DWORD dwIndex, WSABUF* recvBuffer, DWORD* numRecvBytes);
	SOCKET Accept(DWORD dwIndex);

private:
	void Listen(LPVOID lpvParam);
	bool initWinSock();
	bool getAvailableProtocols();

protected:

	EventHandler callback_function_accept;
	EventHandler callback_function_read;
	EventHandler callback_function_close;

};

