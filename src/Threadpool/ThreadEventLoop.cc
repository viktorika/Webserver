#include "ThreadEventLoop.h"

ThreadEventLoop::ThreadEventLoop()
:	loop(new EventLoop()),
	thread(new Thread(std::bind(&ThreadEventLoop::Loop,this)))
{
	
}

ThreadEventLoop::~ThreadEventLoop(){
	
}

void ThreadEventLoop::Loop(){
	loop->loop();
}

void ThreadEventLoop::start(){
	thread->start();
}

SP_EventLoop ThreadEventLoop::getLoop(){
	return loop;
}
