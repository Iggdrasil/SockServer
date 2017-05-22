#include "stdafx.h"
#include "router_service.h"
#include "TListener.h"
#include <iostream>
using std::cout;
using std::endl;

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
		idle();
		
		if (!ptr->empty())
		{
			PLISTENSOCK conn = ptr->pop();
			//conn->m_pClient->printData();
			//preprocess(conn->m_pClient);
			processed_.push_back(conn);
			cout << "Processed: " << conn->hSocket << endl;

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

bool comparator_sock_struct_err(tagLISTENSOCK* s)
{
	if (s != NULL)
	{
		return s->hSocket == SOCKET_ERROR;
	}
	return true;
}

void router_service::idle()
{
	if (processed_.empty())
	{
		return;
	}
	std::list<tagLISTENSOCK*>::iterator it = processed_.begin();
	std::list<tagLISTENSOCK*>::iterator itEnd = processed_.end();
	std::list<tagLISTENSOCK*>::iterator itFound = std::find_if(it, itEnd, comparator_sock_struct_err);
	while (itFound != itEnd)
	{
		processed_.erase(itFound);
		itFound = std::find_if(it, itEnd, comparator_sock_struct_err);
	}

}
