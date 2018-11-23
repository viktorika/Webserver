#pragma once

#include "Packet.h"
#include "Http_conn.h"
#include "Reactor/EventLoop.h"
#include "Threadpool/ThreadpoolEventLoop.h"
#include "log/Logging.h"

class Server{
private:
	SP_EventLoop loop;
	SP_Channel serverchannel;
	UP_ThreadpoolEventLoop iothreadpool;
	int listenfd;
	std::unordered_map<int,SP_Http_conn> Httpmap;	
	void handleconn();
	void handleclose(WP_Channel channel); 
	void deletemap(SP_Channel channel);

public:
	Server(const char * port,int threadnum);
	~Server();
	void start();	
};
