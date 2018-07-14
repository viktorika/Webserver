objects=main.o Server.o Http_conn.o Mimetype.o Packet.o EventLoop.o Epoll.o Channel.o TimerManager.o Logging.o AsyncLogging.o LogStream.o LogFile.o FileUtil.o ThreadpollEventLoop.o ThreadEventLoop.o Thread.o

g11=g++ -std=c++11
 
Webserver:$(objects)
	$(g11) -o Webserver $(objects) -lpthread

main.o:main.cc
	$(g11) -g -c main.cc

Server.o:Server.cc Server.h 
	$(g11) -g -c Server.cc

Http_conn.o:Http_conn.cc Http_conn.h
	$(g11) -g -c Http_conn.cc

Mimetype.o:Mimetype.cc Mimetype.h
	$(g11) -g -c Mimetype.cc

EventLoop.o:Reactor/EventLoop.h Reactor/EventLoop.cc 
	$(g11) -g -c Reactor/EventLoop.cc

Epoll.o:Reactor/Epoll.h Reactor/Epoll.cc 
	$(g11) -g -c Reactor/Epoll.cc

Channel.o:Reactor/Channel.h Reactor/Channel.cc
	$(g11) -g -c Reactor/Channel.cc

TimerManager.o:Reactor/TimerManager.h Reactor/TimerManager.cc
	$(g11) -g -c Reactor/TimerManager.cc

ThreadpollEventLoop.o:Threadpoll/ThreadpollEventLoop.h Threadpoll/ThreadpollEventLoop.cc
	$(g11) -g -c Threadpoll/ThreadpollEventLoop.cc

ThreadEventLoop.o:Threadpoll/ThreadEventLoop.h Threadpoll/ThreadEventLoop.cc
	$(g11) -g -c Threadpoll/ThreadEventLoop.cc

Thread.o:Threadpoll/Thread.h Threadpoll/Thread.cc
	$(g11) -g -c Threadpoll/Thread.cc

Packet.o:Packet.cc Packet.h
	$(g11) -g -c Packet.cc

Logging.o:log/Logging.h log/Logging.cc
	$(g11) -g -c log/Logging.cc

AsyncLogging.o:log/AsyncLogging.h log/AsyncLogging.cc
	$(g11) -g -c log/AsyncLogging.cc

LogStream.o:log/LogStream.h log/LogStream.cc
	$(g11) -g -c log/LogStream.cc

LogFile.o:log/LogFile.h log/LogFile.cc
	$(g11) -g -c log/LogFile.cc

FileUtil.o:log/FileUtil.h log/FileUtil.cc
	$(g11) -g -c log/FileUtil.cc 

.PHONY:clean
clean:
	rm Webserver $(objects)
