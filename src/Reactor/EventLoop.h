#pragma once

#include "Epoll.h"
#include "TimerManager.h"
#include <queue>
#include "../Mutex/MutexLock.h"

class Channel;
class Epoll;
class TimerManager;
typedef std::shared_ptr<Channel> SP_Channel;
typedef std::weak_ptr<Channel> WP_Channel;
typedef std::shared_ptr<Epoll> SP_Epoll;
typedef std::shared_ptr<TimerManager> SP_TimerManager;

class EventLoop:public std::enable_shared_from_this<EventLoop>{
private:
	typedef std::function<void()> Functor;
	std::vector<Functor> pendingfunctorq;
	int wakeupfd;
	SP_Channel wakeupchannel;
	SP_Epoll poller;
	bool looping;
	static bool quit;
	SP_TimerManager timermanager;
	MutexLock mutex;

public:
	EventLoop();
	void addPoller(SP_Channel channel);
	void updatePoller(SP_Channel channel);
	void removePoller(SP_Channel channel);
	void loop();
	void addTimer(SP_Channel channel,int timeout);
	void queueInLoop(Functor &&cb);
	void doPendingFunctors();
	static void setquit(int);
};

typedef std::shared_ptr<EventLoop> SP_EventLoop;
typedef std::weak_ptr<EventLoop> WP_EventLoop;
