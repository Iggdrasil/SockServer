#pragma once
#include <queue>
#include <mutex>

template<typename T> class safeQueue
{

	std::mutex _mutex;
protected:
	std::queue<T> _q;
public:
	safeQueue() {}
	~safeQueue() {}

	void push(T val)
	{
		_mutex.lock();
		_q.push(val);
		_mutex.unlock();
	};

	T pop()
	{
		_mutex.lock();
		T val;
		std::swap(val, _q.front());
		_q.pop();
		_mutex.unlock();
		return val;
	};

	bool empty()
	{
		_mutex.lock();
		return _q.empty();
		_mutex.unlock();
	}

};