#pragma once

#include "Thread.h"

class Threadpoll{
private:
	vector<SP_Thread> thread;	
	int threadnum;	
	int index;

public:
	Threadpoll(int Threadnum);
	~Threadpoll();
	void start();
	SP_EventLoop getNextloop();
};

typedef std::unique_ptr<Threadpoll> UP_Threadpoll;
