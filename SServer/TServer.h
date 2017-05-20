#pragma once
#include "TListener.h"
#include "TClient.h"


#define RECV_BUFFER_SIZE 8192

class TServer :
	public TListener
{

public:
	TServer(TMessageQueue* mQueue);
	~TServer();

	static HRESULT OnAccept(LPVOID lpvParam, DWORD dwIndex);
	static HRESULT OnReceive(LPVOID lpvParam, DWORD dwIndex);
	static HRESULT OnDisconnect(LPVOID lpvParam, DWORD dwIndex);

	static TClient* OnConnect(SOCKET client_sock, int m_nPort);
};

