#pragma once

#include "conf/Conf.h"
#include <sys/eventfd.h>
#include <sys/socket.h>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <netdb.h>

#define MAXLINE 4096 

typedef struct sockaddr SA;
typedef struct epoll_event SE;
/*
 *全部为包裹函数
 */
int Socket(int family,int type,int protocol);
int Bind(int sockfd,SA *myaddr,socklen_t addrlen);
int Listen(int sockfd,int backlog);
int Accept(int sockfd,SA *cliaddr,socklen_t *addrlen);
int Fcntl(int fd,int cmd);
int Fcntl(int fd,int cmd,long arg);
int setnonblocking(int sockfd);
int Epoll_create(int size);
int Epoll_ctl(int epfd,int op,int fd,SE *event);
int Epoll_wait(int epfd,SE *events,int maxevents,int timeout);
ssize_t readn(int fd,std::string &inbuffer,bool &zero);
ssize_t writen(int fd,const void *vptr,size_t n);
int Open(const char *pathname,int oflags,mode_t mode);
int Close(int sockfd);
int Setsockopt(int sockfd,int level,int optname,const void *optval,socklen_t optlen);
int tcp_listen(const char *hostname,const char *service,socklen_t *addrlenp);
int Eventfd(unsigned int initval,int flags);
