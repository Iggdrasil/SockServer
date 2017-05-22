#include "stdafx.h"
#include "TServer.h"
#include <iostream>
using std::cout;
using std::endl;



TServer::TServer(TMessageQueue* mQueue)
	:TListener(mQueue)
{
	callback_function_accept = OnAccept;
	callback_function_read = OnReceive;
	callback_function_close = OnDisconnect;
}


TServer::~TServer()
{
}

HRESULT TServer::OnAccept(LPVOID lpvParam, DWORD dwIndex)
{
	TServer *pListener = (TServer *)lpvParam;
	SOCKET client_sock = pListener->Accept(dwIndex);

	if (INVALID_SOCKET == client_sock)
	{
		return S_FALSE;
	}

	/*
	тут мы получили сокет нового клиента и вызываем обработчик подключения
	который в случае успеха возвращает указатель на класс Tcleint
	*/
	

	TClient* pClient = TServer::OnConnect(client_sock, pListener->port_);
	if (NULL == pClient)
	{
		return S_FALSE;
	}

	pListener->listeningSockets[pListener->numListeningSockets - 1].m_pClient = pClient;

	pListener->mQueue_->push(&pListener->listeningSockets[pListener->numListeningSockets - 1]);

	return S_OK;
}

HRESULT TServer::OnReceive(LPVOID lpvParam, DWORD dwIndex)
{
	TServer *pListener = (TServer *)lpvParam;
	//CClient* lpClient = pListener->m_ListeningSockets[dwIndex].m_pClient;
	SOCKET m_hSocket = pListener->listeningSockets[dwIndex].hSocket;

	char m_szRecvBuffer[RECV_BUFFER_SIZE];
	WSABUF m_RecvBuffer;
	DWORD  m_dwNumRecvBytes;
	m_RecvBuffer.buf = m_szRecvBuffer;
	m_RecvBuffer.len = RECV_BUFFER_SIZE;

	HRESULT hr = TListener::OnRecive(m_hSocket, dwIndex, &m_RecvBuffer, &m_dwNumRecvBytes);
	if (S_OK != hr)
	{
		return S_FALSE;
	}

	pListener->listeningSockets[dwIndex].m_pClient->addData(m_RecvBuffer.buf, m_dwNumRecvBytes);

	return S_OK;
}


TClient* TServer::OnConnect(SOCKET client_sock, int m_nPort)
{
	//новое подключение к LOGINSERVER
	TClient* pClient = new TClient;
	if (NULL == pClient)
	{
		return NULL;
	}

	return pClient;
}



HRESULT TServer::OnDisconnect(LPVOID lpvParam, DWORD dwIndex)
{
	TServer *pListener = (TServer *)lpvParam;
	SOCKET s = pListener->listeningSockets[dwIndex].hSocket;
	cout << "Disconnected: " << s << endl;
	pListener->OnClose(dwIndex);
	return S_OK;
}