#pragma once
#include "TMessageQueue.h"
#include <Windows.h>

class router_service :
	public TMessageQueue
{
public:
	router_service();
	~router_service();

	static void processThread(LPVOID lpvParam);
	bool startProcess();
};

