#pragma once

#include <functional>
#include <memory>
#include <sys/epoll.h>

class Channel{
private:
	typedef std::function<void()> CallBack;
	int fd;
	int events;
	int revents;
	int index;
	CallBack readhandler;
	CallBack writehandler;

public:
	Channel();
	void setReadhandler(CallBack &&readHandler);
	void setWritehandler(CallBack &&writeHandler);
	void handleEvent();
	void setFd(int Fd);
	void setRevents(int Revents);
	void setEvents(int Events);
	int getFd();
	int getRevents();
};

typedef std::shared_ptr<Channel> SP_Channel;
