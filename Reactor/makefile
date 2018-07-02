EventLoop.o:EventLoop.h EventLoop.cc Epoll.o
	g++ -std=c++11 -g -c EventLoop.cc

Epoll.o:Epoll.h Epoll.cc Channel.o
	g++ -std=c++11 -g -c Epoll.cc

Channel.o:Channel.h Channel.cc
	g++ -std=c++11 -g -c Channel.cc
