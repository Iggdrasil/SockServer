#include "stdafx.h"
#include "TServer.h"


TServer::TServer()
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
	������� � ������ ������ ���������� ��������� �� ����� �cleint
	
	CClient* pClient = CLoginServer::OnConnect(client_sock, pListener->m_nPort);
	if (NULL == pClient)
	{
		return S_FALSE;
	}
	*/
	// ������� ��������� �� ������ � ��������� ��� �������� ������� � ������ ����.
	//pListener->listeningSockets[pListener->numListeningSockets - 1].m_pClient = pClient;

	return S_OK;
}

HRESULT TServer::OnReceive(LPVOID lpvParam, DWORD dwIndex)
{
	TServer *pListener = (TServer *)lpvParam;
	//CClient* lpClient = pListener->m_ListeningSockets[dwIndex].m_pClient;
	SOCKET m_hSocket = pListener->listeningSockets[dwIndex].hSocket;


/*
	char m_szRecvBuffer[RCV_BUFFER_SIZE];
	WSABUF m_RecvBuffer;
	DWORD  m_dwNumRecvBytes;

	m_RecvBuffer.buf = m_szRecvBuffer;
	m_RecvBuffer.len = RCV_BUFFER_SIZE;


	//READ PACKET SIZE
	HRESULT hr = COverlappedSocket::OnRecive(m_hSocket, dwIndex, &m_RecvBuffer, &m_dwNumRecvBytes);
	if (S_OK != hr)
		return S_FALSE;

	WORD len = *(WORD*)&m_RecvBuffer.buf[0];
	m_RecvBuffer.buf = new char[len];
	m_RecvBuffer.len = len;

	//READ PACKET BODY
	hr = COverlappedSocket::OnRecive(m_hSocket, dwIndex, &m_RecvBuffer, &m_dwNumRecvBytes);
	if (S_OK != hr) return S_FALSE;

	BYTE* data_buf = new BYTE[len + 2];
	memcpy(&data_buf[0], &len, 2);
	memcpy(&data_buf[2], m_RecvBuffer.buf, len);

	//��� ����� ����� ��� ������ ����������� ���������� �������


	delete[] data_buf;
	delete[] m_RecvBuffer.buf;
	*/

	return S_OK;
}

/*
CClient* TServer::OnConnect(SOCKET client_sock, int m_nPort)
{
	//����� ����������� � LOGINSERVER
	CClient* pClient = new CClient;
	if (NULL == pClient) return NULL;

	return pClient;
}
*/


HRESULT TServer::OnDisconnect(LPVOID lpvParam, DWORD dwIndex)
{
	TServer *pListener = (TServer *)lpvParam;
	//CClient* lpClient = pListener->m_ListeningSockets[dwIndex].m_pClient;

	//��� ����� ����� ��� ����������� ������� ������� ����������

	return S_OK;
}