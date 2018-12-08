#pragma once

#include "ThreadEventLoop.h"

class ThreadpoolEventLoop{
private:
	vector<SP_ThreadEventLoop> elv;	
	int threadnum;	
	int index;

public:
	static void* operator new(size_t size){
		return use_memory(3);
	}

	static void operator delete(void *p){
		free_memory(3,p);
	}

	ThreadpoolEventLoop(int Threadnum);
	~ThreadpoolEventLoop();
	void start();
	SP_EventLoop getNextloop();
};

typedef std::unique_ptr<ThreadpoolEventLoop> UP_ThreadpoolEventLoop;
