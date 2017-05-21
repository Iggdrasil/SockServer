#pragma once
#include "TMessageQueue.h"

typedef void* LPVOID;

class router_service :
	public TMessageQueue
{
public:
	router_service();
	~router_service();

	static void processThread(LPVOID lpvParam);
	bool startProcess();
};

