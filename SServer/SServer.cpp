// SServer.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "TServer.h"


int main()
{
	TServer srv;
	srv.startServer(4399);
	for (;;)
	{
		Sleep(5);
		//Update();//� ����� ��� � ������ ������� ����� �������, ���������� ������������ � ����-����� ���������� ����������.
	}
    return 0;
}

