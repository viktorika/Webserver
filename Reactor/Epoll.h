#pragma once

#include "Channel.h"
#include "../Packet.h"
#include "../Http_conn.h"
#include <unordered_map>
#include <vector>
#include <memory>

#define MAXFDS 10000
#define EVENTS 4096

using namespace std;


class Epoll{
private:
	int epollfd;
	vector<SE> events;
	unordered_map<int,SP_Channel>Channelmap;
public:
	Epoll();
	void add(SP_Channel request);
	void update(SP_Channel request);
	void del(SP_Channel request);
	vector<SP_Channel> poll();
};

typedef shared_ptr<Epoll> SP_Epoll;
