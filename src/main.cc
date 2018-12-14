#include "Server.h"
#include <signal.h>
#include "conf/Conf.h"

int main(int argc,char **argv){
	init_memorypool();
	const char *parm="hvc:";
	char conf[100]="conf/WebServer.conf";
	int opt;
	while(~(opt=getopt(argc,argv,parm))){
		switch(opt){
			case 'h':
				printf("Options:\n");
				printf("  -h\t: this help\n");
				printf("  -v\t: show version and exiet\n");
				printf("  -c\t: set configuration file(default: conf/WebServer.conf)\n)");
				return 0;
			case 'v':printf("WebServer version WebServer/1.11\n");return 0;
			case 'c':strncpy(conf,optarg,99);break;
			default:break;
		}
	}
	getconf().init(conf);
	getCache().init();
	signal(SIGPIPE,SIG_IGN);
	signal(SIGINT,EventLoop::setquit);
	signal(SIGQUIT,EventLoop::setquit);
	Server server(getconf().getport().c_str(),getconf().getio_thread());
	server.start();
}
