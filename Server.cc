#include "Server.h"

Server::Server(int port)
:	loop(new EventLoop()),
	serverchannel(new Channel())
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
	while((connfd=Accept(listenfd,(SA *)&cliaddr,&clilen))>0){
		perror("accept one");
		setnonblocking(connfd);
		SP_Channel connchannel(new Channel());
		connchannel->setFd(connfd);
		connchannel->setRevents(EPOLLIN|EPOLLET);
		SP_Http_conn connhttp(new Http_conn(connchannel));
		loop->addPoller(connchannel);
		Httpmap[connfd]=connhttp;
	}
}

void Server::start(){
	serverchannel->setRevents(EPOLLIN|EPOLLET);
	serverchannel->setReadhandler(bind(&Server::handleconn,this));
	loop->addPoller(serverchannel);
	perror("start");
	loop->loop();
}
