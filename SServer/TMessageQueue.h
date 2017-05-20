#pragma once
#include "SafeQueue.h"
#include "TClient.h"

class TMessageQueue : public safeQueue<TClient*>
{
public:
	TMessageQueue();
	~TMessageQueue();
};

