#pragma once

#include "../Threadpool/Thread.h"
#include "../Mutex/MutexLock.h"
#include "../Mutex/Condition.h"
#include "LogStream.h"
#include "LogFile.h"
#include <vector>
#include "FixedBuffer.h"

class AsyncLogging:noncopyable{
private:
	void threadFunc();
	typedef FixedBuffer<kLargeBuffer> Buffer;
	typedef std::vector<std::shared_ptr<Buffer>> BufferVector;
	typedef std::shared_ptr<Buffer> BufferPtr;
	const int flushInterval;
	bool running;
	std::string basename;
	Thread thread_;
	MutexLock mutex;
	Condition cond;
	BufferPtr currentBuffer;
	BufferPtr nextBuffer;
	BufferVector buffers;
	//CountDownLatch latch;

public:
	AsyncLogging(const std::string logFileName,int FlushInterval=2);
	~AsyncLogging();
	void append(const char *logfile,int len);
	void start();
	void stop();	

};

typedef std::unique_ptr<AsyncLogging,decltype(deleteElement<AsyncLogging>)*> UP_AsyncLogging;
