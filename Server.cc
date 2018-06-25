#include "Server.h"

Server::Server(int port){
	for(int i=0;i<MAXFDS;++i)
		http_conn[i].setsockfd(i);
	listenfd=Socket(AF_INET,SOCK_STREAM,0);
    setnonblocking(listenfd);
	struct sockaddr_in servaddr;
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(port);
    Bind(listenfd,(SA *)&servaddr,sizeof(servaddr));
    Listen(listenfd,LISTENQ);
    epfd=Epoll_create(MAXFDS);
	SE ev;
    ev.events=EPOLLIN|EPOLLET;
	ev.data.fd=listenfd;
	Epoll_ctl(epfd,EPOLL_CTL_ADD,listenfd,&ev);
	perror("listenning");	
}

Server::~Server(){

}

void Server::start(){
	for(;;){
        int nfds=Epoll_wait(epfd,events,MAXFDS,-1);
        for(int i=0;i<nfds;++i){
            int fd=events[i].data.fd;
            if(listenfd==fd){
				struct sockaddr_storage cliaddr;
                socklen_t clilen=sizeof(cliaddr);
                int connfd=Accept(listenfd,(SA *)&cliaddr,&clilen);
				perror("accept one");
                setnonblocking(connfd);
				SE ev;
                ev.events=EPOLLIN|EPOLLET;
                ev.data.fd=connfd;
                Epoll_ctl(epfd,EPOLL_CTL_ADD,connfd,&ev);			
            }
            else if(events[i].events&EPOLLIN){
				perror("something read");
				http_conn[fd].parse();
			}
        }
	}
}
