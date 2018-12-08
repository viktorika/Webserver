#include "Conf.h"

#define DEFAULT_IO_THREAD 3
#define DEFAULT_PORT "8080"
#define DEFAULT_LISTENQ 2048
#define DEFAULT_STORAGE "page/"
#define DEFAULT_KEEP_ALIVED 20000
#define DEFAULT_LOGFILE "log/WebServer.log"

int Conf::getio_thread(){
	return io_thread;
}

string Conf::getport(){
	return port;
}

int Conf::getlistenq(){
	return listenq;
}

int Conf::getkeep_alived(){
	return keep_alived;
}

string Conf::getstorage(){
	return storage;
}

string Conf::getlogfile(){
	return logfile;
}

int Conf::getcapacity(){
	return capacity;
}

int Conf::getpos(string &buf,int start,int end,bool flag){
	for(;start<end;++start){
		if(flag){
			if(' '==buf[start]||'\t'==buf[start])
				return start;
		}
		else{
			if(' '!=buf[start]&&'\t'!=buf[start])
				return start;
		}
	}
	return start;
}

void Conf::Separate_kv(map<string,string> &m,string &buf){
	int kstart=getpos(buf,0,buf.size(),false);
	int kend=getpos(buf,kstart,buf.size(),true);
	int vstart=getpos(buf,kend,buf.size(),false);
	int vend=getpos(buf,vstart,buf.size(),true);
	if(vstart!=buf.size())
		m[buf.substr(kstart,kend-kstart)]=buf.substr(vstart,vend-vstart);
}

void Conf::solve_comment(string &buf){
	int last=buf.find("#",0);
	if(string::npos==last)
		return;
	buf=buf.substr(0,last);
	return;
}

Conf::Conf(){

}

void Conf::init(char *path){
	strncpy(conf,path,99);
	map<string,string>m;
	fstream file;
	file.open(conf,ios::in);
	string buf;
	while(!file.eof()){
		getline(file,buf);
		solve_comment(buf);
		if(""==buf)
			continue;
		Separate_kv(m,buf);
	}
	file.close();
	if(m.find("IO_thread")!=m.end())
		io_thread=stoi(m["IO_thread"]);
	else
		io_thread=DEFAULT_IO_THREAD;
	if(m.find("port")!=m.end())
		port=m["port"];
	else
		port=DEFAULT_PORT;
	if(m.find("listenq")!=m.end())
		listenq=stoi(m["listenq"]);
	else
		listenq=DEFAULT_LISTENQ;
	if(m.find("storage")!=m.end())
		storage=m["storage"];
	else
		storage=DEFAULT_STORAGE;
	if(m.find("keep-alived")!=m.end())
		keep_alived=stoi(m["keep-alived"]);
	else
		keep_alived=DEFAULT_KEEP_ALIVED;
	if(m.find("logfile")!=m.end())
		logfile=m["logfile"];
	else
		logfile=DEFAULT_LOGFILE;
	if(m.find("capacity")!=m.end())
		capacity=stoi(m["capacity"]);
	else
		capacity=10;
}

Conf& getconf(){
	static Conf conf;
	return conf;
}
