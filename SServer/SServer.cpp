// SServer.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "TServer.h"
#include "router_service.h"


int main()
{
	router_service rc;
	if (!rc.startProcess())
	{
		return 0;
	}
	TServer srv(&rc);
	srv.startServer(4399);
	for (;;)
	{
		Sleep(5);
		//Update();
	}
    return 0;
}

