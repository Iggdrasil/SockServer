#pragma once
#include <WinSock2.h>
#include "TClient.h"
#include "TMessageQueue.h"
#define VERSION_MAJOR      2
#define VERSION_MINOR      0
#define MAX_LISTENING_SOCKETS    1024

typedef HRESULT(*EventHandler)(LPVOID lParam, DWORD dwIndex);

typedef struct tagLISTENSOCK
{
	SOCKET hSocket;
	LPWSAPROTOCOL_INFO ProtoInfo;
	TClient* m_pClient;

}LISTENSOCK, *PLISTENSOCK;


class TListener
{
	DWORD numAvailableProtocols;

	LPWSAPROTOCOL_INFO availableProtocols;
	HANDLE listeningEventObj[MAX_LISTENING_SOCKETS];

protected:
	DWORD port_;
	DWORD numListeningSockets;
	LISTENSOCK listeningSockets[MAX_LISTENING_SOCKETS];
	TMessageQueue* mQueue_;
public:
	TListener(TMessageQueue* mQueue);
	~TListener();

public:
	bool startServer(int port);

	static void startListenThreadProc(LPVOID lpvParam);
	static HRESULT OnRecive(SOCKET socket, DWORD dwIndex, WSABUF* recvBuffer, DWORD* numRecvBytes);
	HRESULT OnClose(DWORD dwIndex);

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

