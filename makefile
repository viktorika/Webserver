objects=main.o Server.o Http_conn.o Mimetype.o Packet.o EventLoop.o Epoll.o Channel.o TimerManager.o Logging.o AsyncLogging.o LogStream.o LogFile.o FileUtil.o ThreadpoolEventLoop.o ThreadEventLoop.o Thread.o

origins=main.cc Server.cc Http_conn.cc Mimetype.cc Packet.cc Reactor/EventLoop.cc Reactor/Epoll.cc Reactor/Channel.cc Reactor/TimerManager.cc log/Logging.cc log/AsyncLogging.cc log/LogStream.cc log/LogFile.cc log/FileUtil.cc Threadpool/ThreadpoolEventLoop.cc Threadpool/ThreadEventLoop.cc Threadpool/Thread.cc

g11=g++ -std=c++11
 
Webserver:$(objects)
	$(g11) -o Webserver $(objects) -lpthread

$(objects):$(origins)
	$(g11) -g -c $(origins)

.PHONY:clean
clean:
	rm Webserver $(objects)
