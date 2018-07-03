#include "EventLoop.h"

EventLoop::EventLoop()
:	poller(new Epoll()),
	looping(false),
	quit(false),
	timermanager(new TimerManager())
{

}

void EventLoop::addPoller(SP_Channel channel,int timeout){
	poller->add(channel);
	if(timeout)
		timermanager->addTimer(channel,timeout);
}

void EventLoop::updatePoller(SP_Channel channel,int timeout){
	poller->update(channel);
	if(timeout)
		timermanager->addTimer(channel,timeout);
}

void EventLoop::removePoller(SP_Channel channel){
	poller->del(channel);
}

void EventLoop::loop(){
	std::vector<SP_Channel> temp;
	while(!quit){
		temp.clear();
		temp=poller->poll();
		for(int i=0;i<temp.size();++i)
			temp[i]->handleEvent();
		//执行其他任务
		timermanager->handleExpiredEvent();
	}
}
