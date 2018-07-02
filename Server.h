#pragma once

#include "Packet.h"
#include "Http_conn.h"
#include "Reactor/EventLoop.h"

class Server{
private:
	SP_EventLoop loop;
	SP_Channel serverchannel;
	int listenfd;
	std::unordered_map<int,SP_Http_conn> Httpmap;	
	void handleconn();

public:
	Server(int port);
	~Server();
	void start();	
};
