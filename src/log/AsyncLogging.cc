#include "AsyncLogging.h"

AsyncLogging::AsyncLogging(const std::string logFileName,int FlushInterval)
:	flushInterval(FlushInterval),
	running(false),
	basename(logFileName),
	thread_(std::bind(&AsyncLogging::threadFunc,this),"Logging"),
	mutex(),
	cond(mutex),
	currentBuffer(newElement<Buffer>(),deleteElement<Buffer>),
	nextBuffer(newElement<Buffer>(),deleteElement<Buffer>)
{

}

AsyncLogging::~AsyncLogging(){
	if(running)
		stop();
}

void AsyncLogging::append(const char *logline,int len){
	MutexLockGuard lock(mutex);
	if(currentBuffer->avail()>len)
		currentBuffer->append(logline,len);
	else{
		buffers.emplace_back(currentBuffer);
		if(nextBuffer)
			currentBuffer=std::move(nextBuffer);
		else
			currentBuffer.reset(newElement<Buffer>(),deleteElement<Buffer>);
		currentBuffer->append(logline,len);
		cond.notify();
	}
}

void AsyncLogging::threadFunc(){
	BufferPtr newBuffer1(newElement<Buffer>(),deleteElement<Buffer>);
	BufferPtr newBuffer2(newElement<Buffer>(),deleteElement<Buffer>);
	BufferVector buffersToWrite;
	LogFile output(basename);
	while(running){
		{
			MutexLockGuard lock(mutex);
			if(buffers.empty())
				cond.waitForSeconds(flushInterval);
			buffers.emplace_back(currentBuffer);
			currentBuffer=std::move(newBuffer1);
			buffersToWrite.swap(buffers);
			if(!nextBuffer)
				nextBuffer=std::move(newBuffer2);
		}
		for(auto &wi:buffersToWrite)
			output.append(wi->data(),wi->length());
		if(!newBuffer1)
			newBuffer1.reset(newElement<Buffer>(),deleteElement<Buffer>);
		if(!newBuffer2)
			newBuffer2.reset(newElement<Buffer>(),deleteElement<Buffer>);
		buffersToWrite.clear();
		output.flush();
	}
	output.flush();
}

void AsyncLogging::start(){
	running=true;
	thread_.start();
}

void AsyncLogging::stop(){
	running=false;
	cond.notify();
	thread_.join();
}
