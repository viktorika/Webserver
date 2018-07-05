A Webserver with c++
====

Introduction
----
本项目为C++11写的基于http协议的Web服务器，写这个的目的是为了让半年来看的东西学以致用．

Envoirment
----
* OS:Ubuntu 16.04.4
* Complier: g++ 4.8

## Build

	make

## Usage

	page里放请求的页面，启动服务器：./Webserver [-n threadnum] [-p port]

Technical points
* 采用Reactor模式+EPOLL(ET)非阻塞IO
* 使用小根堆+unordered_map实现定时器以关闭超时连接
* 使用线程池参考muduo的one loop per thread的思想
* 使用了智能指针，bind和function等c++11的新特性
* 用状态机解析了http请求，写法较优雅．可以参考一下
