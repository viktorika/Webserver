#pragma once

#include "Packet.h"
#include "Http_conn.h"

#define MAXFDS 1000

class Server{
private:
	int listenfd,epfd;
	SE events[MAXFDS];
	Http_conn http_conn[MAXFDS];
public:
	Server(int port);
	~Server();
	void start();
	
};
