#pragma once

#include "Packet.h"
#include "Http_conn.h"
#include "Reactor/EventLoop.h"
#include "Threadpool/ThreadpoolEventLoop.h"
#include "log/Logging.h"


#include "openssl/bio.h"
#include "openssl/ssl.h"
#include "openssl/err.h"

typedef std::shared_ptr<SSL_CTX> SP_SSL_CTX;

class Server{
private:
	SP_EventLoop loop;
	SP_Channel serverchannel;
	UP_ThreadpoolEventLoop iothreadpool;
	int listenfd;
	SP_SSL_CTX ctx;
	std::unordered_map<int,SP_Http_conn> Httpmap;	
	void handleconn();
	void handleclose(WP_Channel channel); 
	void deletemap(SP_Channel channel);
	void ssl_hand_shake(WP_Channel channel);

public:
	Server(const char * port,int threadnum);
	~Server();
	void start();	
};
