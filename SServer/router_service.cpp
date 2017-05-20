#include "stdafx.h"
#include "router_service.h"


router_service::router_service()
{
}


router_service::~router_service()
{
}

void router_service::processThread(LPVOID lpvParam)
{
	router_service* ptr = (router_service*)lpvParam;
	TClient* cli = ptr->pop();
}

bool router_service::startProcess()
{
	DWORD ListenThreadID;
	HANDLE hThread = (HANDLE)CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)processThread, LPVOID(this), 0, &ListenThreadID);

	if (hThread == NULL)
		return false;

	return true;
}
