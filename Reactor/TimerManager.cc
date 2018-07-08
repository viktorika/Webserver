#include "TimerManager.h"

typedef struct timeval ST;

TimerNode::TimerNode(SP_Channel Channel,int timeout)
:	channel((Channel))
{
	ST now;
	gettimeofday(&now,NULL);
	expiredtime=(LL)now.tv_sec*1000+now.tv_usec/1000+timeout;
}

TimerNode::~TimerNode(){

}

LL TimerNode::getExpiredtime(){
	return expiredtime;
}

void TimerNode::update(int timeout){
	ST now;
	gettimeofday(&now,NULL);
	expiredtime=(LL)now.tv_sec*1000+now.tv_usec/1000+timeout;
}

bool TimerNode::isValib(){
	ST now;
	gettimeofday(&now,NULL);
	LL temp=(LL)now.tv_sec*1000+now.tv_usec/1000;
	if(temp<expiredtime)
		return true;
	return false;
}

bool TimerNode::isDeleted(){
	return channel->isDeleted();
}

SP_Channel TimerNode::getChannel(){
	return channel;	
}

void TimerManager::addTimer(SP_Channel channel,int timeout){
	SP_TimerNode timernode(new TimerNode(channel,timeout));;
	timerheap.push(timernode);
	timermap[channel->getFd()]=std::move(timernode);
}

void TimerManager::handleExpiredEvent(){
	while(!timerheap.empty()){
		SP_TimerNode now=timerheap.top();
		if(now->isDeleted()||!now->isValib()){
			timerheap.pop();
			if(now==timermap[now->getChannel()->getFd()]){
				timermap.erase(now->getChannel()->getFd());
				now->getChannel()->handleClose();
			}
		}
		else
			break;
	}
}
