#pragma once

#include "../noncopyable.h"
#include <pthread.h>
#include <functional>
#include <memory>
#include <string>
#include <assert.h>
#include "../MemoryPool/MemoryPool.h"

struct ThreadData{
	typedef std::function<void()> ThreadFunc;
    ThreadFunc func;
    std::string name;

    ThreadData(const ThreadFunc &Func,const std::string &Name)
    :   func(Func),
        name(Name)
    {

    }

    void runInThread(){
        func();
 	}
	
	static void* operator new(size_t){
		return use_memory(7);
	}	
	
	static void operator delete(void *p){
		free_memory(7,p);
	}
};

class Thread:noncopyable{
public:
	typedef std::function<void()> ThreadFunc;
	explicit Thread(const ThreadFunc&&,const std::string& name=std::string());
	~Thread();
	void start();
	int join();
	bool started()const;
	const std::string& name()const;
	static void* operator new(size_t size){
		return use_memory(9);
	}

	static void operator delete(void *p){
		free_memory(9,p);
	}

private:
	void setDefaultName();
	bool started_;
	bool joined_;
	pthread_t pthreadId;
	ThreadFunc func;
	std::string name_;
};

typedef std::shared_ptr<Thread> SP_Thread;
typedef std::unique_ptr<Thread> UP_Thread;
