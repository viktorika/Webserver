#include "Server.h"
#include <signal.h>

int main(int argc,char **argv){
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
	signal(SIGPIPE,SIG_IGN);
	Server server(port,threadnum);
	server.start();
}
