#include "Thread.h"

struct ThreadData{
	typedef std::function<void()> ThreadFunc;
	ThreadFunc func;
	std::string name;
	
	ThreadData(const ThreadFunc &Func,const std::string &Name)
	:	func(Func),
		name(Name)
	{
		
	}
	
	void runInThread(){
		func();
	}
};

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
	delete data;
	return NULL;
}

void Thread::start(){
	assert(!started_);
	started_=true;
	ThreadData *data=new ThreadData(func,name_);
	if(pthread_create(&pthreadId,NULL,&startThread,data)){
		started_=false;
		delete data;
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
