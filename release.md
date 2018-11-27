version 1:
----
* 使用了epoll复用，单线程处理IO,解决了基本的http解析问题．
* 待处理：有时候数据没有读完就解析的bug，可采用线程池处理IO．

version 2:
----
* 参考muduo的写法加入了Reactor模式，基于事件触发．
* 待处理：Reactor写得还不够完美，计时器还未加入（这部分还没读懂），http的错误处理也还没写，线程池部分还未加，还有很多小细节方面未修改（另外还有一>些读取bug未处理．

version 3:
----
* 增加了Timer计时器，解决http长连接的问题．
* 修复了一些bug，例如浏览器访问时请求favicon.ico图片的问题．
### **Timer计时器的处理逻辑：**
#### Timer里有两个数据结构：unordered_map和priority_queue，优先队列存放者TimerNode节点，只要节点的时间到了，或者该节点对应的channel事件关闭了那么>    该节点就可以删除，同时unorder_map是fd映射TimerNode节点，此TimerNode节点为存储在优先队列里的时间最久TimerNode节点，这里要注意，一个channel对应多个T    imerNode节点，当该channel的TimerNode节点全部从优先队列中弹出时，删除掉该事件．这是我想到的比较好的Timer的处理方案．

version 4:
----
* 增加了线程池模块，加大了服务器的并发性能，采用one loop per thread的机制，想参考muduo，无奈不太好理解，暂时写得比较简陋，有待以后改进．
* 优化部分代码，提高一点性能.

version 5:
----
* 扩展功能，支持命令行选项，-n为线程数目，-p为端口号，这里注意，我是主线程accept，其他线程处理读写操作的，所以必定有一个主线程，故-n 3表示1个主线>    程，3个副线程.
* 参照UNIX网络编程，用tcp_listen代替了socket,bind,listen过程，支持IPV6.

version 6:
---
* 重构了http_conn，用状态机解决了http解析问题，修复了解析bug，而且写法用了function和bind自认为比较优雅，可以参考一下.
* 增加了http错误处理功能，暂时统一按400错误码返回.以后有待改进.

version 7:
----
* 使用RAII机制封装锁，让线程更安全
* 优化blocking queue，子线程在执行主线程给的任务时，把emptyqueue置换给pendingfunctorqueue，之后对emptyqueue进行操作就可以了，这样可以减少临界区>的代码，在主线程accept往子线程添加任务时反应更迅速

version 8:
----
* 参考muduo，用双缓冲技术实现了log日志
* 重构thread有关代码

### ** Log实现逻辑: **
#### 首先是Logger类，Logger类里面有Impl类，其实具体实现是Impl类，我也不懂muduo为何要再封装一层，那么我们来说说Impl干了什么，在初始化的时候Impl会把时间信息存到LogStream的缓冲区里，在我们实际用Log的时候，实际写入的缓冲区也是LogStream，在析构的时候Impl会把当前文件和行数等信息写入到LogStream，再把LogStream里的内容写到AsyncLogging的缓冲区中，当然这时候我们要先开启一个后端线程用于把缓冲区的信息写到文件里.
#### 然后来说说LogStream类，里面其实就一个Buffer缓冲区，是用来暂时存放我们写入的信息的.还有就是重载运算符，因为我们采用的是C++ Stream的风格
#### 再来说说AsyncLogging类，这个是最核心的部分，我们知道在多线程程序中写Log无非就是前端往后端写，后端往硬盘写，首先前面提到了将LogStream的内容写到了AsyncLogging缓冲区里，也就是前端往后端写，这个过程通过append函数实现，后端实现通过threadfunc函数，两个线程的同步和等待通过互斥锁和条件变量来实现，具体实现使用了双缓冲技术，双缓冲技术的基本思路:准备两块buffer，A和B,前端往A写数据，后端从B里面往硬盘写数据，当A写满后，交换A和B，如此反复．不过实际的实现的话和这个还是有点区别，具体看代码吧
#### 剩下的LogFile类和FileUtil类其实没什么好说的，就是把文件用RAII机制封装了，LogFile在FileUtil的基础上再封装增加了点功能罢了．

version 9:
----
* 使用eventfd用于线程通信，将分配fd的操作视作io操作封装在Channel一同放进epoll，更好的管理事件
* 实现了自己的内存池，进一步优化性能

####内存池具体实现参考STL allocator和github上的第一个memorypool
