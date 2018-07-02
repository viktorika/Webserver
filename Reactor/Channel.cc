#include "Channel.h"

void Channel::setReadhandler(CallBack &&readHandler){
	readhandler=readHandler;
}

void Channel::setWritehandler(CallBack &&writeHandler){
	writehandler=writehandler;
}

void Channel::handleEvent(){
	if(events&EPOLLIN)
		readhandler();		
}

Channel::Channel(){
	
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

int Channel::getFd(){
	return fd;
}

int Channel::getRevents(){
	return revents; 
}
