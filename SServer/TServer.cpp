#include "stdafx.h"
#include "TServer.h"



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
	��� �� �������� ����� ������ ������� � �������� ���������� �����������
	������� � ������ ������ ���������� ��������� �� ����� Tcleint
	*/
	TClient* pClient = TServer::OnConnect(client_sock, pListener->port_);
	if (NULL == pClient)
	{
		return S_FALSE;
	}

	pListener->mQueue_->push(pClient);
	//mQueue_->push(pClient);
	// ������� ��������� �� ������ � ��������� ��� �������� ������� � ������ ����.
	//pListener->listeningSockets[pListener->numListeningSockets - 1].m_pClient = pClient;

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


/*


	BYTE* data_buf = new BYTE[len + 2];
	memcpy(&data_buf[0], &len, 2);
	memcpy(&data_buf[2], m_RecvBuffer.buf, len);

	//��� ����� ����� ��� ������ ����������� ���������� �������


	delete[] data_buf;
	delete[] m_RecvBuffer.buf;
	*/

	return S_OK;
}


TClient* TServer::OnConnect(SOCKET client_sock, int m_nPort)
{
	//����� ����������� � LOGINSERVER
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
	//CClient* lpClient = pListener->m_ListeningSockets[dwIndex].m_pClient;

	//��� ����� ����� ��� ����������� ������� ������� ����������

	return S_OK;
}