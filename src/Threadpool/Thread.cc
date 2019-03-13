#include "Thread.h"

Thread::Thread(const ThreadFunc&& Func,const std::string &n)
:	started_(false),
	joined_(false),
	pthreadId(0),
	func(Func),
	name_(n)
{
	setDefaultName();
}

Thread::~Thread(){
	if(started_&&!joined_)
		pthread_detach(pthreadId);
}

void Thread::setDefaultName(){
	if(name_.empty())
		name_+="Thread";
}

void* startThread(void *obj){
	ThreadData* data=(ThreadData *)obj;
	data->runInThread();
	deleteElement<ThreadData>(data);
	return NULL;
}

void Thread::start(){
	assert(!started_);
	started_=true;
	ThreadData *data=newElement<ThreadData>(func,name_);
	if(pthread_create(&pthreadId,NULL,&startThread,data)){
		started_=false;
		deleteElement<ThreadData>(data);
	}
}

int Thread::join(){
	assert(started_);
	assert(!joined_);
	joined_=true;
	return pthread_join(pthreadId,NULL);
}

bool Thread::started()const{
	return started_;
}


const std::string& Thread::name()const{
	return name_;
}
