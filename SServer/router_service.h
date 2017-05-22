#pragma once
#include <list>
#include "TMessageQueue.h"
#include "TClient.h"
#include "THttpHeaderParser.h"


typedef void* LPVOID;

class router_service :
	public TMessageQueue
{
	std::list<tagLISTENSOCK*> processed_;
	THttpHeaderParser httpHeaderParser_;
public:
	router_service();
	~router_service();

	static void processThread(LPVOID lpvParam);
	bool startProcess();
	void process(LPVOID lpvParam);

private:
	bool preprocess(TClient* cli);
	void idle();
};

