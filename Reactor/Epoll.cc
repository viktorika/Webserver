#include "Epoll.h"

Epoll::Epoll()
:	events(EVENTS)
{
	epollfd=Epoll_create(MAXFDS);
}

Epoll::~Epoll(){
	Close(epollfd);
}

void Epoll::add(const SP_Channel &request){
	int fd=request->getFd();
	SE ev;
	ev.events=request->getRevents();
	ev.data.fd=fd;
	Epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&ev);
	Channelmap[fd]=move(request);	
}

void Epoll::update(const SP_Channel &request){
	int fd=request->getFd();
	SE ev;
	ev.events=request->getRevents();
	ev.data.fd=fd;
	Epoll_ctl(epollfd,EPOLL_CTL_MOD,fd,&ev);
}

void Epoll::del(const SP_Channel &request){
	int fd=request->getFd();
	SE ev;
	ev.events=request->getRevents();
	ev.data.fd=fd;
	Epoll_ctl(epollfd,EPOLL_CTL_DEL,fd,&ev);
	Channelmap.erase(fd);
}

void Epoll::poll(std::vector<SP_Channel> &req){
	int nfds=epoll_wait(epollfd,&*events.begin(),EVENTS,EPOLLWAIT_TIME);
	for(int i=0;i<nfds;++i){
		int fd=events[i].data.fd;
		SP_Channel temp=Channelmap[fd];
		temp->setEvents(events[i].events);
		req.emplace_back(std::move(temp));
	}
}
