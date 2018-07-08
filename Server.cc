#include "Server.h"

Server::Server(const char * port,int threadnum)
:	loop(new EventLoop()),
	serverchannel(new Channel(loop)),
	threadpoll(new Threadpoll(threadnum))
{
	listenfd=tcp_listen(NULL,port,NULL);
	setnonblocking(listenfd);
	serverchannel->setFd(listenfd);
}

Server::~Server(){
	Close(listenfd);
}

void Server::handleconn(){
	struct sockaddr_storage cliaddr;
	socklen_t clilen=sizeof(cliaddr);
	int connfd;
	while((connfd=Accept(listenfd,(SA *)&cliaddr,&clilen))>=0){
		printf("accepet fd=%d\n",connfd);
		setnonblocking(connfd);
		SP_EventLoop nextloop=threadpoll->getNextloop();
		SP_Channel connchannel(new Channel(nextloop));
		connchannel->setFd(connfd);
		connchannel->setRevents(EPOLLIN|EPOLLET);
		WP_Channel wpchannel=connchannel;
		connchannel->setClosehandler(bind(&Server::handleclose,this,wpchannel));
		SP_Http_conn connhttp(new Http_conn(connchannel));
		Httpmap[connfd]=move(connhttp);
		nextloop->queueInLoop(bind(&EventLoop::addPoller,nextloop.get(),move(connchannel)));
	}
}

void Server::start(){
	threadpoll->start();
	serverchannel->setRevents(EPOLLIN|EPOLLET);
	serverchannel->setReadhandler(bind(&Server::handleconn,this));
	loop->addPoller(serverchannel);
	perror("start");
	loop->loop();
}

void Server::handleclose(WP_Channel channel){
	SP_Channel spchannel=channel.lock();
	loop->queueInLoop(bind(&Server::deletemap,this,spchannel));
	spchannel->getLoop().lock()->removePoller(spchannel);
}

void Server::deletemap(SP_Channel channel){
	Httpmap.erase(channel->getFd());
}
