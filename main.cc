#include "Server.h"

int main(int argc,char **argv){
	/*printf("ThreadData=%lu\n",sizeof(ThreadData));
	printf("timernode=%lu\n",sizeof(TimerNode));
	printf("http=%lu\n",sizeof(Http_conn));
	printf("Mimetype=%lu\n",sizeof(Mimetype));
	printf("Channel=%lu\n",sizeof(Channel));
	printf("Epoll=%lu\n",sizeof(Epoll));
	printf("EventLoop=%lu\n",sizeof(EventLoop));
	printf("TimerManager=%lu\n",sizeof(TimerManager));
	printf("Thread=%lu\n",sizeof(Thread));
	printf("ThreadEventLoop=%lu\n",sizeof(ThreadEventLoop));
	printf("ThreadpoolEventLoop=%lu\n",sizeof(ThreadpoolEventLoop));
	printf("AsyncLogging=%lu\n",sizeof(AsyncLogging));
	printf("FileUtil=%lu\n",sizeof(FileUtil));
	printf("LogFile=%lu\n",sizeof(LogFile));
	//printf("Logging=%lu\n",sizeof(Logging));
	printf("LogStream=%lu\n",sizeof(LogStream));*/
	init_memorypool();
	char port[10]="8080";
	int threadnum=3;
	const char *parm="p:n:";
	int opt;
	while(~(opt=getopt(argc,argv,parm))){
		switch(opt){
			case 'p':strncpy(port,optarg,9);break;
			case 'n':threadnum=atoi(optarg);break;
			default:break;
		}
	}
	if(threadnum<=0)
		fprintf(stderr,"threadnum must be a positive number!\n");
	Server server(port,threadnum);
	server.start();
}
