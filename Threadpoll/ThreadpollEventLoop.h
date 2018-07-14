#pragma once

#include "ThreadEventLoop.h"

class ThreadpollEventLoop{
private:
	vector<SP_ThreadEventLoop> elv;	
	int threadnum;	
	int index;

public:
	ThreadpollEventLoop(int Threadnum);
	~ThreadpollEventLoop();
	void start();
	SP_EventLoop getNextloop();
};

typedef std::unique_ptr<ThreadpollEventLoop> UP_ThreadpollEventLoop;
