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
		fprintf(stderr,"accept error\n");
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

ssize_t readn(int fd,std::string &inbuffer){
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
				perror("read error");
				return -1;
			}
		}	
		else if(!nread)
			break;
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
		perror("open file failed");
	return n;
}
