#include "stdafx.h"
#include "TListener.h"


TListener::TListener(TMessageQueue* mQueue)
	:mQueue_(mQueue)
{
}


TListener::~TListener()
{
}

void TListener::startListenThreadProc(LPVOID lpvParam)
{
	TListener* ptr = (TListener*)lpvParam;
	ptr->Listen(lpvParam);
	return;
}

bool TListener::startServer(int port)
{
	if (!initWinSock())
	{
		return false;
	}

	if (!getAvailableProtocols())
	{
		return false;
	}

	port_ = port;

	DWORD ListenThreadID;
	HANDLE hThread = (HANDLE)CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)startListenThreadProc, LPVOID(this), 0, &ListenThreadID);

	if (hThread == NULL)
	{
		return false;
	}

	return true;
}

HRESULT TListener::OnRecive(SOCKET socket, DWORD dwIndex, WSABUF* recvBuffer, DWORD* numRecvBytes)
{
	DWORD dwFlags = 0;

	int nResult = WSARecv(socket,
		recvBuffer,
		1,
		numRecvBytes,
		&dwFlags,
		NULL,
		NULL);

	if (nResult == SOCKET_ERROR)
	{
		return S_FALSE;
	}

	return S_OK;
}

HRESULT TListener::OnClose(DWORD dwIndex)
{
	closesocket(listeningSockets[dwIndex].hSocket);
	
	return S_OK;
}

SOCKET TListener::Accept(DWORD dwIndex)
{
	// accept connection
	SOCKET s = WSAAccept(listeningSockets[dwIndex].hSocket, NULL, NULL, NULL, (DWORD)NULL);
	if (s == INVALID_SOCKET)
	{
		return INVALID_SOCKET;
	}

	int nResult = 0;
	// create event object
	listeningEventObj[numListeningSockets] = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (listeningEventObj[numListeningSockets] == NULL)
	{
		closesocket(s);
		return SOCKET_ERROR;
	}

	// задаем два события которые нам интересны: приход данных и дисконнект
	//при желании добавляем новые
	nResult = WSAEventSelect(s, listeningEventObj[numListeningSockets], FD_READ | FD_CLOSE);
	if (nResult == SOCKET_ERROR)
	{
		CloseHandle(listeningEventObj[numListeningSockets]);
		closesocket(s);
		return SOCKET_ERROR;
	}

	listeningSockets[numListeningSockets].hSocket = s;

	listeningSockets[numListeningSockets].ProtoInfo = NULL;
	if (++numListeningSockets == MAX_LISTENING_SOCKETS)
	{
		return SOCKET_ERROR;
	}

	return s;
}

void TListener::Listen(LPVOID lpvParam)
{
	numListeningSockets = 0;
	for (DWORD i = 0; i < numAvailableProtocols; ++i)
	{
		LPWSAPROTOCOL_INFO pInfo;
		SOCKET s;

		pInfo = &availableProtocols[i];
		if (pInfo == NULL)
		{
			continue;
		}

		if ((pInfo->dwServiceFlags1 & XP1_CONNECTIONLESS) ||
			(!(pInfo->dwServiceFlags1 & XP1_GUARANTEED_DELIVERY)) ||
			(!(pInfo->dwServiceFlags1 & XP1_GUARANTEED_ORDER)) ||
			(!(pInfo->iAddressFamily == AF_INET)))
		{
			continue;
		}

		s = WSASocket(0, 0, 0, pInfo, 0, WSA_FLAG_OVERLAPPED);
		if (s == INVALID_SOCKET)
		{
			continue;
		}


		SOCKADDR_IN addr;

		memset(&addr, 0, sizeof(SOCKADDR_IN));
		// assign family and port
		addr.sin_family = (u_short)pInfo->iAddressFamily;
		addr.sin_port = htons((u_short)port_);

		// bind
		int nResult = bind(s, (LPSOCKADDR)&addr, sizeof(SOCKADDR_IN));
		if (nResult == SOCKET_ERROR)
		{
			closesocket(s);
			continue;
		}

		// create event object
		listeningEventObj[numListeningSockets] = CreateEvent(NULL, FALSE, FALSE, NULL);
		if (listeningEventObj[numListeningSockets] == NULL)
		{
			closesocket(s);
			continue;
		}

		// turn on notifications
		nResult = WSAEventSelect(s, listeningEventObj[numListeningSockets], FD_ACCEPT);
		if (nResult == SOCKET_ERROR)
		{
			CloseHandle(listeningEventObj[numListeningSockets]);
			closesocket(s);
			continue;
		}

		// now listen
		nResult = listen(s, SOMAXCONN);
		if (nResult == SOCKET_ERROR)
		{
			CloseHandle(listeningEventObj[numListeningSockets]);
			closesocket(s);
			continue;
		}

		// fill in socket handle
		listeningSockets[numListeningSockets].hSocket = s;
		
		// fill in protocol info
		listeningSockets[numListeningSockets].ProtoInfo = pInfo;

		if (++numListeningSockets == MAX_LISTENING_SOCKETS)
		{
			break;
		}

		while (true)
		{
			DWORD dwIndex;
			dwIndex = WaitForMultipleObjects(numListeningSockets,
				listeningEventObj,
				FALSE,
				INFINITE);

			//OnAccept(lpvParam, dwIndex - WAIT_OBJECT_0);
			int it = dwIndex - WAIT_OBJECT_0;
			WSAEVENT hEventObject = listeningEventObj[it];
			WSANETWORKEVENTS info;

			SOCKET s = listeningSockets[it].hSocket;
			WSAEnumNetworkEvents(s, hEventObject, &info);

			if (info.lNetworkEvents & FD_ACCEPT)
			{
				callback_function_accept(lpvParam, it);
			}

			if (info.lNetworkEvents & FD_READ)
			{
				callback_function_read(lpvParam, it);
			}

			if (info.lNetworkEvents & FD_CLOSE)
			{
				callback_function_close(lpvParam, it);
			}
		}

		return;
	}
}

bool TListener::initWinSock()
{
	int           nError;
	WORD          wVersionRequested;
	WSADATA       WsaData;
	bool          bRtn = true;

	wVersionRequested = MAKEWORD(VERSION_MAJOR, VERSION_MINOR);
	nError = WSAStartup(wVersionRequested, &WsaData);
	if (nError)
	{
		bRtn = false;
	}
	else
	{
		if (LOBYTE(WsaData.wVersion) != VERSION_MAJOR ||
			HIBYTE(WsaData.wVersion) != VERSION_MINOR)
		{
			WSACleanup();
			bRtn = false;
		}
	}
	return bRtn;
}

bool TListener::getAvailableProtocols()
{
	DWORD dwNumBytes = 0;
	numAvailableProtocols = WSAEnumProtocols(NULL, NULL, &dwNumBytes);
	if (numAvailableProtocols == SOCKET_ERROR && WSAGetLastError() != WSAENOBUFS)
	{
		return false;
	}

	availableProtocols = (LPWSAPROTOCOL_INFO)malloc(dwNumBytes);
	if (availableProtocols == NULL)
	{
		return false;
	}

	numAvailableProtocols = WSAEnumProtocols(NULL, availableProtocols, &dwNumBytes);
	if (numAvailableProtocols == SOCKET_ERROR)
	{
		return false;
	}
	return true;
}
