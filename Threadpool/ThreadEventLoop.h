#pragma once

#include "../Reactor/EventLoop.h"
#include "Thread.h"
#include <vector>

class ThreadEventLoop{
private:
	SP_EventLoop loop;
	UP_Thread thread;
	void Loop();

public:
	ThreadEventLoop();
	~ThreadEventLoop();
	void start();
	SP_EventLoop getLoop();
};

typedef std::shared_ptr<ThreadEventLoop> SP_ThreadEventLoop;
