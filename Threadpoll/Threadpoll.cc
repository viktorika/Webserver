#include "Threadpoll.h"

Threadpoll::Threadpoll(int Threadnum)
:	threadnum(Threadnum),
	index(0)
{
	thread.reserve(threadnum);
	for(int i=0;i<threadnum;++i){
		SP_Thread t(new Thread());
		thread.emplace_back(t);
	}	
}

Threadpoll::~Threadpoll(){
	thread.clear();
}

void Threadpoll::start(){
	for(int i=0;i<threadnum;++i)
		thread[i]->start();
}

SP_EventLoop Threadpoll::getNextloop(){
	index=(index+1)%threadnum;
	return thread[index]->getLoop();
}
