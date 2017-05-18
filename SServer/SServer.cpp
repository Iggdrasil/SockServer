// SServer.cpp: определяет точку входа для консольного приложения.
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
		//Update();//я думаю что в каждом сервере нужна функция, вызываемая периодически с боле-менее постоянным интервалом.
	}
    return 0;
}

