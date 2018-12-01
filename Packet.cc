#include "Packet.h"

int Socket(int family,int type,int protocol){
	int n;
	if((n=socket(family,type,protocol))<0)
		fprintf(stderr,"socket error\n");
	return n;
}

int Bind(int sockfd,SA *myaddr,socklen_t addrlen){
	int n;
	if((n=bind(sockfd,myaddr,addrlen))<0)
		fprintf(stderr,"bind error\n");
	return n;
}

int Listen(int sockfd,int backlog){
	int n;
	if((n=listen(sockfd,backlog))<0)
		fprintf(stderr,"listen error\n");
	return n;
}

int Accept(int sockfd,SA *cliaddr,socklen_t *addrlen){
	int n;
	if((n=accept(sockfd,cliaddr,addrlen))<0)
		//fprintf(stderr,"accept error\n");
		;
	return n;
}

int Fcntl(int fd,int cmd){
	int n;
	if((n=fcntl(fd,cmd))<0)
		fprintf(stderr,"fcntl error\n");
	return n;
}

int Fcntl(int fd,int cmd,long arg){
	int n;
	if((n=fcntl(fd,cmd,arg))<0)
		fprintf(stderr,"fcntl error\n");
	return n;
}

int setnonblocking(int sockfd){
	int val=Fcntl(sockfd,F_GETFL,0);
	Fcntl(sockfd,F_SETFL,val|O_NONBLOCK);
}

int Epoll_create(int size){
	int n;
	if((n=epoll_create(size))<0)
		fprintf(stderr,"epoll create error\n");
	return n;
}

int Epoll_ctl(int epfd,int op,int fd,SE *event){
	int n;
	if((n=epoll_ctl(epfd,op,fd,event))<0)
		fprintf(stderr,"epoll ctl error\n");
	return n;
}

int Epoll_wait(int epfd,SE *events,int maxevents,int timeout){
	int n;
	if((n=epoll_wait(epfd,events,maxevents,timeout))<0)
		fprintf(stderr,"epoll wait error\n");
	return n;
}

ssize_t readn(int fd,std::string &inbuffer,bool &zero){
	ssize_t nread;
	ssize_t readSum=0;
	while(true){
		char buff[MAXLINE];
		if((nread=read(fd,buff,MAXLINE))<0){
			if(EINTR==errno)
				continue;
			else if(EAGAIN==errno)
				return readSum;
			else{
				fprintf(stderr,"read error\n");
				return -1;
			}
		}	
		else if(!nread){
			zero=true;
			break;
		}
		readSum+=nread;
		inbuffer+=std::string(buff,buff+nread);
	}
	return readSum;
}

ssize_t writen(int fd,const void *vptr,size_t n){
	size_t nleft;
	ssize_t nwritten;
	const char *ptr=(char *)vptr;
	nleft=n;
	while(nleft>0){
		if((nwritten=write(fd,ptr,nleft))<=0){
			if(nwritten<0&&EINTR==errno)
				nwritten=0;
			else
				return -1;
		}
		nleft-=nwritten;
		ptr+=nwritten;
	}
	return n;
}

int Open(const char *pathname,int oflags,mode_t mode){
	int n;
	if((n=open(pathname,oflags,mode))<0)
		fprintf(stderr,"open file failed\n");
	return n;
}

int Close(int sockfd){
	int n;
	if((n=close(sockfd))<0)
		fprintf(stderr,"close sockfd error\n");
	return n;
}

int Setsockopt(int sockfd,int level,int optname,const void *optval,socklen_t optlen){
	int n;
	if((n=setsockopt(sockfd,level,optname,optval,optlen))<0)
		fprintf(stderr,"set sockopt error\n");
	return n;
}

int tcp_listen(const char *host,const char *serv,socklen_t *addrlenp){
	int listenfd,n;
	const int on=1;
	struct addrinfo hints,*res,*ressave;
	bzero(&hints,sizeof(struct addrinfo));
	hints.ai_flags=AI_PASSIVE;
	hints.ai_family=AF_UNSPEC;
	hints.ai_socktype=SOCK_STREAM;
	if((n=getaddrinfo(host,serv,&hints,&res))!=0)
		fprintf(stderr,"tcp_listen error\n");
	ressave=res;
	do{
		listenfd=socket(res->ai_family,res->ai_socktype,res->ai_protocol);
		if(listenfd<0)
			continue;
		Setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
		if(!bind(listenfd,res->ai_addr,res->ai_addrlen))
			break;
		Close(listenfd);
	}while((res=res->ai_next));
	if(!res)
		fprintf(stderr,"tcp_listen error\n");
	Listen(listenfd,getconf().getlistenq());
	if(addrlenp)
		*addrlenp=res->ai_addrlen;
	freeaddrinfo(ressave);
	return listenfd;
}

int Eventfd(unsigned int initval,int flags){
	int n;
	if((n=eventfd(initval,flags))<0)
		fprintf(stderr,"eventfd error\n");
	return n;
}
