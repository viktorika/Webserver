#include "Channel.h"

void Channel::setReadhandler(CallBack &&readHandler){
	readhandler=readHandler;
}

void Channel::setWritehandler(CallBack &&writeHandler){
	writehandler=writeHandler;
}

void Channel::setClosehandler(CallBack &&closeHandler){
	closehandler=closeHandler;
}

void Channel::setDeleted(bool Deleted){
	deleted=Deleted;
}

void Channel::handleEvent(){
	if(events&EPOLLIN)
		readhandler();
	else if(events&EPOLLOUT)
		writehandler();	
}
void Channel::handleClose(){
	closehandler();
}

Channel::Channel(SP_EventLoop Loop)
:	loop(Loop),
	deleted(false),
	First(true)
{
	
}

void Channel::setnotFirst(){
	First=false;
}

Channel::~Channel(){
	LOG<<"delete fd="<<fd;
	Close(fd);
}
void Channel::setFd(int Fd){
	fd=Fd;
}

void Channel::setRevents(int Revents){
	revents=Revents;
}

void Channel::setEvents(int Events){
	events=Events;
}

void Channel::setssl(SP_SSL SSL){
	ssl=SSL;
}

void Channel::setsslconnect(bool ssl_connect){
	sslconnect=ssl_connect;
}

int Channel::getFd(){
	return fd;
}

int Channel::getRevents(){
	return revents; 
}

bool Channel::isDeleted(){
	return deleted;
}

bool Channel::isFirst(){
	return First;
}

WP_EventLoop Channel::getLoop(){
	return loop;
}

SP_SSL Channel::getssl(){
	return ssl;
}

bool Channel::getsslconnect(){
	return sslconnect;
}
