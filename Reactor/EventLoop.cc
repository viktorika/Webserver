#include "EventLoop.h"

EventLoop::EventLoop()
:	poller(new Epoll()),
	looping(false),
	quit(false),
	timermanager(new TimerManager())
{

}

void EventLoop::addPoller(SP_Channel channel){
	poller->add(std::move(channel));
}

void EventLoop::updatePoller(SP_Channel channel){
	poller->update(std::move(channel));
}

void EventLoop::removePoller(SP_Channel channel){
	poller->del(std::move(channel));
}

void EventLoop::loop(){
	std::vector<SP_Channel> temp;
	while(!quit){
		poller->poll(temp);
		for(int i=0;i<temp.size();++i)
			temp[i]->handleEvent();
		temp.clear();
		doPendingFunctors();
		timermanager->handleExpiredEvent();
	}
}

void EventLoop::addTimer(SP_Channel channel,int timeout){
	timermanager->addTimer(std::move(channel),timeout);
}

void EventLoop::queueInLoop(Functor &&cb){
	pthread_mutex_lock(&mutex);
	pendingfunctorq.push(std::move(cb));
	pthread_mutex_unlock(&mutex);
}

void EventLoop::doPendingFunctors(){
	pthread_mutex_lock(&mutex);
	while(!pendingfunctorq.empty()){
		(pendingfunctorq.front())();
		pendingfunctorq.pop();
	}
	pthread_mutex_unlock(&mutex);
}
