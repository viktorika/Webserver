#include "Server.h"

int main(int argc,char **argv){
	Server server(10000,3);
	server.start();
}
