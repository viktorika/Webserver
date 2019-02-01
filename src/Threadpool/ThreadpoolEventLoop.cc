#include "ThreadpoolEventLoop.h"

ThreadpoolEventLoop::ThreadpoolEventLoop(int Threadnum)
:	threadnum(Threadnum),
	index(0)
{
	elv.reserve(threadnum);
	for(int i=0;i<threadnum;++i){
		SP_ThreadEventLoop t(newElement<ThreadEventLoop>(),deleteElement<ThreadEventLoop>);
		elv.emplace_back(t);
	}	
}

ThreadpoolEventLoop::~ThreadpoolEventLoop(){
	elv.clear();
}

void ThreadpoolEventLoop::start(){
	for(auto &evi:elv)
		evi->start();
}

SP_EventLoop ThreadpoolEventLoop::getNextloop(){
	index=(index+1)%threadnum;
	return elv[index]->getLoop();
}
