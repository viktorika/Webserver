#pragma once

#include "Epoll.h"
#include "TimerManager.h"

class Channel;
class Epoll;
class TimerManager;
typedef std::shared_ptr<Channel> SP_Channel;
typedef std::shared_ptr<Epoll> SP_Epoll;
typedef std::shared_ptr<TimerManager> SP_TimerManager;

class EventLoop{
private:
	SP_Epoll poller;
	bool looping;
	bool quit;
	SP_TimerManager timermanager;

public:
	EventLoop();
	void addPoller(SP_Channel channel,int timeout=0);
	void updatePoller(SP_Channel channel,int timeout=0);
	void removePoller(SP_Channel channel);
	void loop();
};

typedef std::shared_ptr<EventLoop> SP_EventLoop;
