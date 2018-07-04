#include "Thread.h"

Thread::Thread()
:	loop(new EventLoop()),
	id(new pthread_t)
{
	
}

Thread::~Thread(){
	pthread_join(*id,NULL);
	delete id;
}

void Thread::start(){
	pthread_create(id,NULL,threadfunc,&loop);
}

void* Thread::threadfunc(void* loop){
	(*(SP_EventLoop *)loop)->loop();
}

SP_EventLoop Thread::getLoop(){
	return loop;
}
