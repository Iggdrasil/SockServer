// SServer.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <WinSock2.h>

#define VERSION_MAJOR      2
#define VERSION_MINOR      0


// Инициализация библиотеки
bool initWinSock()
{
	int err;
	WORD requestedVersion;
	WSADATA WsaData;
	bool ret = true;

	requestedVersion = MAKEWORD(VERSION_MAJOR, VERSION_MINOR);
	err = WSAStartup(requestedVersion, &WsaData);

	if (err)
	{
		ret = false;
	}
	else
	{
		if (LOBYTE(WsaData.wVersion) != VERSION_MAJOR ||
			HIBYTE(WsaData.wVersion) != VERSION_MINOR)
		{
			WSACleanup();
			ret = false;
		}
	}
	return ret;
}

bool getAvailableProtocols(LPWSAPROTOCOL_INFO& availableProtocols)
{
	int protoCnt;
	DWORD numBytes = 0;
	// Получаем необходимый размер структуры под список протоколов
	protoCnt = WSAEnumProtocols(NULL, NULL, &numBytes);

	// Если вернется -1 в количестве протоколов и ошибка, то завершаемся
	if (protoCnt == SOCKET_ERROR && WSAGetLastError() != WSAENOBUFS)
	{
		return false;
	}

	// Должно вернуться WSAENOBUFS, то есть, недостаточный размер буфера
	// и сама функция вернет число протоколов
	availableProtocols = (LPWSAPROTOCOL_INFO)malloc(numBytes);

	protoCnt = WSAEnumProtocols(NULL, availableProtocols, &numBytes);
	if (protoCnt == SOCKET_ERROR )
	{
		return false;
	}
	return true;
}


int main()
{
	initWinSock();
	LPWSAPROTOCOL_INFO availableProtocols;

	getAvailableProtocols(availableProtocols);

    return 0;
}

