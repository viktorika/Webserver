#include "EventLoop.h"

bool EventLoop::quit=false;

EventLoop::EventLoop()
:	poller(newElement<Epoll>(),deleteElement<Epoll>),
	looping(false),
	timermanager(newElement<TimerManager>(),deleteElement<TimerManager>)
{
	wakeupfd=Eventfd(0,EFD_NONBLOCK|EFD_CLOEXEC);
}

void EventLoop::addPoller(SP_Channel channel){
	//timermanager->addTimer(channel,DEFAULT_KEEP_ALIVE_TIME);
	poller->add(channel);
}

void EventLoop::updatePoller(SP_Channel channel){
	poller->update(channel);
}

void EventLoop::removePoller(SP_Channel channel){
	poller->del(channel);
}

void EventLoop::loop(){
	wakeupchannel=SP_Channel(newElement<Channel>(shared_from_this()),deleteElement<Channel>);
	wakeupchannel->setFd(wakeupfd);
	wakeupchannel->setRevents(EPOLLIN|EPOLLET);
	wakeupchannel->setReadhandler(std::bind(&EventLoop::doPendingFunctors,shared_from_this()));
	addPoller(wakeupchannel);
	std::vector<SP_Channel> temp;
	while(!quit){
		poller->poll(temp);
		for(auto &ti:temp)
			ti->handleEvent();
		temp.clear();
		timermanager->handleExpiredEvent();
	}
}

void EventLoop::addTimer(SP_Channel channel,int timeout){
	timermanager->addTimer(std::move(channel),timeout);
}

void EventLoop::queueInLoop(Functor &&cb){
	{
		MutexLockGuard lock(mutex);
		pendingfunctorq.emplace_back(std::move(cb));
	}
	uint64_t buffer=1;
	if(write(wakeupfd,&buffer,sizeof(buffer))<0)
		LOG<<"wake up write error";
}

void EventLoop::doPendingFunctors(){
	uint64_t buffer;
	if(read(wakeupfd,&buffer,sizeof(buffer))<0)
		LOG<<"wake up read error";
	std::vector<Functor> next;
	{
		MutexLockGuard lock(mutex);
		next.swap(pendingfunctorq);
	}
	for(auto &ti:next)
		ti();
}

void EventLoop::setquit(int a){
	quit=true;
}
