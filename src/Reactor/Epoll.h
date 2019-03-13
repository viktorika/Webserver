#pragma once

#include "Channel.h"
#include "../Packet.h"
#include "../Http_conn.h"
#include <unordered_map>
#include <vector>
#include <memory>
#include "../MemoryPool/MemoryPool.h"

#define MAXFDS 10000
#define EVENTS 4096
#define EPOLLWAIT_TIME -1

class Epoll{
private:
	int epollfd;
	std::vector<SE> events;
	std::unordered_map<int,SP_Channel>Channelmap;

public:
	Epoll();
	~Epoll();
	void add(const SP_Channel &request);
	void update(const SP_Channel &request);
	void del(const SP_Channel &request);
	void poll(std::vector<SP_Channel> &req);
};

typedef std::shared_ptr<Epoll> SP_Epoll;
