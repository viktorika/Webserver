#pragma once

#include "Epoll.h"

class EventLoop{
private:
	SP_Epoll poller;
	bool looping;
	bool quit;
public:
	EventLoop();
	void addPoller(shared_ptr<Channel> channel);
	void updatePoller(shared_ptr<Channel> channel);
	void removePoller(shared_ptr<Channel> channel);
	void loop();
};

typedef std::shared_ptr<EventLoop> SP_EventLoop;
