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
page里放请求的页面，启动服务器：./Webserver [-n threadnum] [-p port]

version 1:
----
* 使用了epoll复用，单线程处理IO,解决了基本的http解析问题．
* 待处理：有时候数据没有读完就解析的bug，可采用线程池处理IO．

version 2:
----
* 参考muduo的写法加入了Reactor模式，基于事件触发．
* 待处理：Reactor写得还不够完美，计时器还未加入（这部分还没读懂），http的错误处理也还没写，线程池部分还未加，还有很多小细节方面未修改（另外还有一些读取bug未处理．

version 3:
----
* 增加了Timer计时器，解决http长连接的问题．
* 修复了一些bug，例如浏览器访问时请求favicon.ico图片的问题．
### **Timer计时器的处理逻辑：**
#### Timer里有两个数据结构：unordered_map和priority_queue，优先队列存放者TimerNode节点，只要节点的时间到了，或者该节点对应的channel事件关闭了那么该节点就可以删除，同时unorder_map是fd映射TimerNode节点，此TimerNode节点为存储在优先队列里的时间最久TimerNode节点，这里要注意，一个channel对应多个TimerNode节点，当该channel的TimerNode节点全部从优先队列中弹出时，删除掉该事件．这是我想到的比较好的Timer的处理方案．

version 4:
----
* 增加了线程池模块，加大了服务器的并发性能，采用one loop per thread的机制，想参考muduo，无奈不太好理解，暂时写得比较简陋，有待以后改进．
* 优化部分代码，提高一点性能.

version 5:
----
* 扩展功能，支持命令行选项，-n为线程数目，-p为端口号，这里注意，我是主线程accept，其他线程处理读写操作的，所以必定有一个主线程，故-n 3表示1个主线程，3个副线程.
* 参照UNIX网络编程，用tcp_listen代替了socket,bind,listen过程，支持IPV6.
