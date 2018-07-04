#include "Server.h"

Server::Server(int port,int threadnum)
:	loop(new EventLoop()),
	serverchannel(new Channel(loop)),
	threadpoll(new Threadpoll(threadnum))
{
	listenfd=Socket(AF_INET,SOCK_STREAM,0);
    setnonblocking(listenfd);
	struct sockaddr_in servaddr;
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(port);
    Bind(listenfd,(SA *)&servaddr,sizeof(servaddr));
    Listen(listenfd,LISTENQ);
	serverchannel->setFd(listenfd);
}

Server::~Server(){

}

void Server::handleconn(){
	struct sockaddr_storage cliaddr;
	socklen_t clilen=sizeof(cliaddr);
	int connfd;
	while((connfd=Accept(listenfd,(SA *)&cliaddr,&clilen))>=0){
		printf("accept fd=%d\n",connfd);
		setnonblocking(connfd);
		SP_EventLoop nextloop=threadpoll->getNextloop();
		SP_Channel connchannel(new Channel(nextloop));//暂时只用同一个loop，之后增加线程池后修改
		connchannel->setFd(connfd);
		connchannel->setRevents(EPOLLIN|EPOLLET);
		connchannel->setClosehandler(bind(&Server::handleclose,this,connchannel));
		SP_Http_conn connhttp(new Http_conn(connchannel));
		Httpmap[connfd]=connhttp;
		nextloop->queueInLoop(bind(&EventLoop::addPoller,nextloop.get(),connchannel));
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

void Server::handleclose(SP_Channel channel){
	printf("close fd=%d\n",channel->getFd());
	//Httpmap.erase(channel->getFd());
	loop->queueInLoop(bind(&Server::deletemap,this,channel));
	channel->getLoop()->removePoller(channel);
}

void Server::deletemap(SP_Channel channel){
	Httpmap.erase(channel->getFd());
}
