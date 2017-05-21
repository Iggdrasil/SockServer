#pragma once
#include "SafeQueue.h"

struct tagLISTENSOCK;

class TMessageQueue : public safeQueue<tagLISTENSOCK*>
{
public:
	TMessageQueue();
	~TMessageQueue();
};

