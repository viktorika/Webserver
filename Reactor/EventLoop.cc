#include "EventLoop.h"

EventLoop::EventLoop()
:	poller(new Epoll()),
	looping(false),
	quit(false),
	timermanager(new TimerManager())
{

}

void EventLoop::addPoller(SP_Channel channel){
	poller->add(channel);
}

void EventLoop::updatePoller(SP_Channel channel){
	poller->update(channel);
}

void EventLoop::removePoller(SP_Channel channel){
	poller->del(channel);
}

void EventLoop::loop(){
	std::vector<SP_Channel> temp;
	while(!quit){
		poller->poll(temp);
		for(auto &ti:temp)
			ti->handleEvent();
		temp.clear();
		doPendingFunctors();
		timermanager->handleExpiredEvent();
	}
}

void EventLoop::addTimer(SP_Channel channel,int timeout){
	timermanager->addTimer(std::move(channel),timeout);
}

void EventLoop::queueInLoop(Functor &&cb){
	MutexLockGuard lock(mutex);
	pendingfunctorq.push(std::move(cb));
}

void EventLoop::doPendingFunctors(){
	MutexLockGuard lock(mutex);
	while(!pendingfunctorq.empty()){
		(pendingfunctorq.front())();
		pendingfunctorq.pop();
	}
}
