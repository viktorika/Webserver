#include "Http_conn.h"

void Http_conn::init(){
	pos=0;
	inbuffer="";
	outbuffer="";
	path="index.html";//默认路径
	header.clear();
}

Http_conn::Http_conn(){
	init();
}

Http_conn::~Http_conn(){
	
}

void Http_conn::setsockfd(int sockfd){
	this->sockfd=sockfd;
}

/*
 从inbuffer中找到从pos开始的第一个c字符
 */
bool Http_conn::Read(string &msg,string str){
	int next=inbuffer.find(str,pos);
	if(string::npos==next)
		return false;
	msg=inbuffer.substr(pos,next-pos);
	pos=next+str.length();
	return true;
}

METHODSTATE Http_conn::parseMethod(){
	string msg;
	if(!Read(msg," /"))
		return PARSE_METHOD_ERROR;
	else if("GET"==msg)
		method=METHOD_GET;
	else if("POST"==msg)
		method=METHOD_POST;
	else
		return PARSE_METHOD_ERROR;
	if(!Read(path," "))
		return PARSE_METHOD_ERROR;
	if(!Read(msg,"\r\n"))
		return PARSE_METHOD_ERROR;
	else if("HTTP/1.0"==msg)
		version=HTTP_10;
	else if("HTTP/1.1"==msg)
		version=HTTP_11;
	else
		return PARSE_METHOD_ERROR;
	return PARSE_METHOD_SUCCESS;
}

HEADERSTATE Http_conn::parseHeader(){
	while(inbuffer[pos]!='\r'&&inbuffer[pos+1]!='\n'){
		string key,value;
		if(!Read(key,": "))
			return PARSE_HEADER_ERROR;
		if(!Read(value,"\r\n"))
			return PARSE_HEADER_ERROR;
		header[key]=value;
	}
	return PARSE_HEADER_SUCCESS;
}

/*CONTENTSTATE Http_conn::parseContent(){
//暂时只处理get,get没有正文部分
}*/


void Http_conn::parse(){
	if(readn(sockfd,inbuffer)<0){
		perror("read error");
		parsestate=PARSE_ERROR;
		init();
		return;
	}
	if(parseMethod()==PARSE_METHOD_ERROR){
		perror("parse method error");
		parsestate=PARSE_ERROR;
		init();
		return;
	}
	if(parseHeader()==PARSE_HEADER_ERROR){
		perror("parse header error");
		parsestate=PARSE_ERROR;
		init();
		return;
	}
	if(METHOD_POST==method){
		//暂时不处理
	}
	else if(METHOD_GET==method){
		outbuffer="HTTP/1.1 200 OK\r\n";
		if(header.find("Connection")!=header.end()&&("Keep-Alive"==header["Connection"]||"keep-alive"==header["Connection"]))
			outbuffer+=string("Connection: Keep-Alive\r\n")+"Keep-Alive: timeout"+to_string(DEFAULT_KEEP_ALIVE_TIME)+"\r\n";
		int dot_pos=path.find('.');
		string filetype;
		if(string::npos==dot_pos)
			filetype=Mimetype::getMime("default");
		else
			filetype=Mimetype::getMime(path.substr(dot_pos));
		struct stat sbuf;
		if(stat(path.c_str(),&sbuf)<0){
			perror("no file");
			parsestate=PARSE_ERROR;
			return;
		}
		outbuffer += "Content-Type: " + filetype + "\r\n";
		outbuffer += "Content-Length: " + to_string(sbuf.st_size) + "\r\n";
        outbuffer += "Server: WWQ's Web Server\r\n";
		outbuffer += "\r\n";
		int src_fd=open(path.c_str(),O_RDONLY,0);
		if(src_fd<0){
			perror("open file failed");
			return;
		}
		char *src_addr=(char *)mmap(NULL,sbuf.st_size,PROT_READ,MAP_PRIVATE,src_fd,0);
		close(src_fd);
		outbuffer+=string(src_addr,src_addr+sbuf.st_size);
		munmap(src_addr,sbuf.st_size);
		cout<<outbuffer;
		send();
		init();
	}
	else{
		parsestate=PARSE_ERROR;
	}
}

void Http_conn::send(){
	const char *buffer=outbuffer.c_str();
	if(!writen(sockfd,buffer,outbuffer.length()))
		perror("writen error");
}
