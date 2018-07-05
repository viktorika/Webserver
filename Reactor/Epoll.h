#pragma once

#include "Channel.h"
#include "../Packet.h"
#include "../Http_conn.h"
#include <unordered_map>
#include <vector>
#include <memory>

#define MAXFDS 10000
#define EVENTS 4096
#define EPOLLWAIT_TIME 2000

class Epoll{
private:
	int epollfd;
	std::vector<SE> events;
	std::unordered_map<int,SP_Channel>Channelmap;
public:
	Epoll();
	~Epoll();
	void add(SP_Channel request);
	void update(SP_Channel request);
	void del(SP_Channel request);
	void poll(std::vector<SP_Channel> &req);
};

typedef std::shared_ptr<Epoll> SP_Epoll;
