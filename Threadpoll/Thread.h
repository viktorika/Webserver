#pragma once

#include "../Reactor/EventLoop.h"
#include <vector>
#include <memory>

class Thread{
private:
	SP_EventLoop loop;
	pthread_t* id;
	static void* threadfunc(void* loop);

public:
	Thread();
	~Thread();
	void start();
	SP_EventLoop getLoop();
};

typedef std::shared_ptr<Thread> SP_Thread;
