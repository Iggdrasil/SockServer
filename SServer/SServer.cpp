// SServer.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "TServer.h"
#include "router_service.h"


int main()
{
	router_service rc;
	TServer srv(&rc);
	srv.startServer(4399);
	for (;;)
	{
		Sleep(5);
		//Update();//� ����� ��� � ������ ������� ����� �������, ���������� ������������ � ����-����� ���������� ����������.
	}
    return 0;
}

