#include "EventLoop.h"

EventLoop::EventLoop()
:	poller(new Epoll()),
	looping(false),
	quit(false)
{

}

void EventLoop::addPoller(SP_Channel channel){
	poller->add(channel);
}

void EventLoop::updatePoller(SP_Channel channel){
	poller->update(channel);
}

void EventLoop::removePoller(SP_Channel channel){
	poller->del(channel);
}

void EventLoop::loop(){
	std::vector<SP_Channel> temp;
	while(!quit){
		temp.clear();
		perror("polling");
		temp=poller->poll();
		perror("polling success");
		for(int i=0;i<temp.size();++i)
			temp[i]->handleEvent();
		//还可以执行其他任务，暂时不写(如检测是否要关闭该事件循环)
	}
}
