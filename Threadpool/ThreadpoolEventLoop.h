#pragma once

#include "ThreadEventLoop.h"

class ThreadpoolEventLoop{
private:
	vector<SP_ThreadEventLoop> elv;	
	int threadnum;	
	int index;

public:
	ThreadpoolEventLoop(int Threadnum);
	~ThreadpoolEventLoop();
	void start();
	SP_EventLoop getNextloop();
};

typedef std::unique_ptr<ThreadpoolEventLoop> UP_ThreadpoolEventLoop;
