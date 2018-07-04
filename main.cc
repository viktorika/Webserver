#include "Server.h"

int main(int argc,char **argv){
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
	Server server(port,threadnum);
	server.start();
}
