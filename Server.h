#pragma once

#include "Packet.h"
#include "Http_conn.h"
#include "Reactor/EventLoop.h"
#include "Threadpoll/Threadpoll.h"

class Server{
private:
	SP_EventLoop loop;
	SP_Channel serverchannel;
	UP_Threadpoll threadpoll;
	int listenfd;
	std::unordered_map<int,SP_Http_conn> Httpmap;	
	void handleconn();
	void handleclose(SP_Channel channel); 
	void deletemap(SP_Channel channel);

public:
	Server(const char * port,int threadnum);
	~Server();
	void start();	
};
