#pragma once

#include <functional>
#include <memory>
#include <sys/epoll.h>
#include "EventLoop.h"
#include "../log/Logging.h"
#include "../MemoryPool/MemoryPool.h"

class EventLoop;
typedef std::shared_ptr<EventLoop> SP_EventLoop;
typedef std::weak_ptr<EventLoop> WP_EventLoop;

class Channel{
private:
	typedef std::function<void()> CallBack;
	int fd;
	int events;
	int revents;
	bool deleted;
	bool First;
	WP_EventLoop loop;
	CallBack readhandler;
	CallBack writehandler;
	CallBack closehandler;	

public:
	Channel(SP_EventLoop Loop);
	~Channel();
	void setReadhandler(CallBack &&readHandler);
	void setWritehandler(CallBack &&writeHandler);
	void setClosehandler(CallBack &&closeHandler);
	void setDeleted(bool Deleted);
	void handleEvent();
	void handleClose();
	void setFd(int Fd);
	void setRevents(int Revents);
	void setEvents(int Events);
	void setnotFirst();
	bool isFirst();
	int getFd();
	int getRevents();
	bool isDeleted();
	WP_EventLoop getLoop();
};

typedef std::shared_ptr<Channel> SP_Channel;
