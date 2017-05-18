#pragma once
#include "TListener.h"
class TServer :
	public TListener
{
public:
	TServer();
	~TServer();

	static HRESULT OnAccept(LPVOID lpvParam, DWORD dwIndex);
	static HRESULT OnReceive(LPVOID lpvParam, DWORD dwIndex);
	static HRESULT OnDisconnect(LPVOID lpvParam, DWORD dwIndex);

	//static CClient* OnConnect(SOCKET client_sock, int m_nPort);
};

