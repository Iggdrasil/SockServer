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
	ptr->process(lpvParam);

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

void router_service::process(LPVOID lpvParam)
{
	router_service* ptr = (router_service*)lpvParam;
	while (true)
	{
		if (!ptr->empty())
		{
			PLISTENSOCK conn = ptr->pop();
			//conn->m_pClient->printData();
			preprocess(conn->m_pClient);
			processed_.push(conn);

		}
		Sleep(5);
	}
}

bool router_service::preprocess(TClient * cli)
{
	char* data = NULL;
	size_t len = 0;
	cli->getdata(data, len);
	if (!httpHeaderParser_.parse(data))
	{
		return false;
	}


	return false;
}
