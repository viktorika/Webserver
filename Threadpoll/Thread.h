#pragma once

#include "../noncopyable.h"
#include <pthread.h>
#include <functional>
#include <memory>
#include <string>
#include <assert.h>

class Thread:noncopyable{
public:
	typedef std::function<void()> ThreadFunc;
	explicit Thread(const ThreadFunc&&,const std::string& name=std::string());
	~Thread();
	void start();
	int join();
	bool started()const;
	const std::string& name()const;

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
