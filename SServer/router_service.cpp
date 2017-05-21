#include "stdafx.h"
#include "router_service.h"
#include "TListener.h"


router_service::router_service()
{
}


router_service::~router_service()
{
}

void router_service::processThread(LPVOID lpvParam)
{
	router_service* ptr = (router_service*)lpvParam;
	while (true)
	{
		if (!ptr->empty())
		{
			TClient* cli = ptr->pop()->m_pClient;
			cli->printData();
		}
		Sleep(5);
	}
}

bool router_service::startProcess()
{
	DWORD ListenThreadID;
	HANDLE hThread = (HANDLE)CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)processThread, LPVOID(this), 0, &ListenThreadID);

	if (hThread == NULL)
	{
		return false;
	}
	return true;
}
