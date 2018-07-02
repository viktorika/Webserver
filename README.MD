A Webserver with c++
====

Introduction
----
本项目为C++11写的基于http协议的Web服务器，写这个的目的是为了让半年来看的东西学以致用．

Envoirment
----
* OS:Ubuntu 16.04.4
* Complier: g++ 4.8

Build
----
make

Usage
----
./Webserver

version 1:
----
* 使用了epoll复用，单线程处理IO,解决了基本的http解析问题．
* 待处理：有时候数据没有读完就解析的bug，可采用线程池处理IO．

version 2:
----
* 参考muduo的写法加入了Reactor模式，基于事件触发．
* 待处理：Reactor写得还不够完美，计时器还未加入（这部分还没读懂），http的错误处理也还没写，线程池部分还未加，还有很多小细节方面未修改（另外还有一些读取bug未处理．
