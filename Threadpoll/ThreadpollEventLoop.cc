#include "ThreadpollEventLoop.h"

ThreadpollEventLoop::ThreadpollEventLoop(int Threadnum)
:	threadnum(Threadnum),
	index(0)
{
	elv.reserve(threadnum);
	for(int i=0;i<threadnum;++i){
		SP_ThreadEventLoop t(new ThreadEventLoop());
		elv.emplace_back(t);
	}	
}

ThreadpollEventLoop::~ThreadpollEventLoop(){
	elv.clear();
}

void ThreadpollEventLoop::start(){
	for(auto &evi:elv)
		evi->start();
}

SP_EventLoop ThreadpollEventLoop::getNextloop(){
	index=(index+1)%threadnum;
	return elv[index]->getLoop();
}
