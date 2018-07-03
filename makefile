Webserver:main.o Server.o Http_conn.o Mimetype.o Packet.o EventLoop.o Epoll.o Channel.o TimerManager.o
	g++ -std=c++11 -o Webserver main.o Server.o Http_conn.o Mimetype.o Packet.o EventLoop.o Epoll.o Channel.o TimerManager.o -lpthread	
main.o:main.cc
	g++ -std=c++11 -g -c main.cc

Server.o:Server.cc Server.h 
	g++ -std=c++11 -g -c Server.cc

Http_conn.o:Http_conn.cc Http_conn.h
	g++ -std=c++11 -g -c Http_conn.cc

Mimetype.o:Mimetype.cc Mimetype.h
	g++ -std=c++11 -g -c Mimetype.cc

EventLoop.o:Reactor/EventLoop.h Reactor/EventLoop.cc 
	g++ -std=c++11 -g -c Reactor/EventLoop.cc

Epoll.o:Reactor/Epoll.h Reactor/Epoll.cc 
	g++ -std=c++11 -g -c Reactor/Epoll.cc

Channel.o:Reactor/Channel.h Reactor/Channel.cc
	g++ -std=c++11 -g -c Reactor/Channel.cc

TimerManager.o:Reactor/TimerManager.h Reactor/TimerManager.cc
	g++ -std=c++11 -g -c Reactor/TimerManager.cc

Packet.o:Packet.cc Packet.h
	g++ -std=c++11 -g -c Packet.cc
