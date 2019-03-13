#include "ThreadEventLoop.h"

ThreadEventLoop::ThreadEventLoop()
:	loop(newElement<EventLoop>(),deleteElement<EventLoop>),
	thread(newElement<Thread>(std::bind(&ThreadEventLoop::Loop,this)),deleteElement<Thread>)
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
