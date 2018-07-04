#include "Http_conn.h"

char favicon[555] = {
  '\x89', 'P', 'N', 'G', '\xD', '\xA', '\x1A', '\xA',
  '\x0', '\x0', '\x0', '\xD', 'I', 'H', 'D', 'R',
  '\x0', '\x0', '\x0', '\x10', '\x0', '\x0', '\x0', '\x10',
  '\x8', '\x6', '\x0', '\x0', '\x0', '\x1F', '\xF3', '\xFF',
  'a', '\x0', '\x0', '\x0', '\x19', 't', 'E', 'X',
  't', 'S', 'o', 'f', 't', 'w', 'a', 'r',
  'e', '\x0', 'A', 'd', 'o', 'b', 'e', '\x20',
  'I', 'm', 'a', 'g', 'e', 'R', 'e', 'a',
  'd', 'y', 'q', '\xC9', 'e', '\x3C', '\x0', '\x0',
  '\x1', '\xCD', 'I', 'D', 'A', 'T', 'x', '\xDA',
  '\x94', '\x93', '9', 'H', '\x3', 'A', '\x14', '\x86',
  '\xFF', '\x5D', 'b', '\xA7', '\x4', 'R', '\xC4', 'm',
  '\x22', '\x1E', '\xA0', 'F', '\x24', '\x8', '\x16', '\x16',
  'v', '\xA', '6', '\xBA', 'J', '\x9A', '\x80', '\x8',
  'A', '\xB4', 'q', '\x85', 'X', '\x89', 'G', '\xB0',
  'I', '\xA9', 'Q', '\x24', '\xCD', '\xA6', '\x8', '\xA4',
  'H', 'c', '\x91', 'B', '\xB', '\xAF', 'V', '\xC1',
  'F', '\xB4', '\x15', '\xCF', '\x22', 'X', '\x98', '\xB',
  'T', 'H', '\x8A', 'd', '\x93', '\x8D', '\xFB', 'F',
  'g', '\xC9', '\x1A', '\x14', '\x7D', '\xF0', 'f', 'v',
  'f', '\xDF', '\x7C', '\xEF', '\xE7', 'g', 'F', '\xA8',
  '\xD5', 'j', 'H', '\x24', '\x12', '\x2A', '\x0', '\x5',
  '\xBF', 'G', '\xD4', '\xEF', '\xF7', '\x2F', '6', '\xEC',
  '\x12', '\x20', '\x1E', '\x8F', '\xD7', '\xAA', '\xD5', '\xEA',
  '\xAF', 'I', '5', 'F', '\xAA', 'T', '\x5F', '\x9F',
  '\x22', 'A', '\x2A', '\x95', '\xA', '\x83', '\xE5', 'r',
  '9', 'd', '\xB3', 'Y', '\x96', '\x99', 'L', '\x6',
  '\xE9', 't', '\x9A', '\x25', '\x85', '\x2C', '\xCB', 'T',
  '\xA7', '\xC4', 'b', '1', '\xB5', '\x5E', '\x0', '\x3',
  'h', '\x9A', '\xC6', '\x16', '\x82', '\x20', 'X', 'R',
  '\x14', 'E', '6', 'S', '\x94', '\xCB', 'e', 'x',
  '\xBD', '\x5E', '\xAA', 'U', 'T', '\x23', 'L', '\xC0',
  '\xE0', '\xE2', '\xC1', '\x8F', '\x0', '\x9E', '\xBC', '\x9',
  'A', '\x7C', '\x3E', '\x1F', '\x83', 'D', '\x22', '\x11',
  '\xD5', 'T', '\x40', '\x3F', '8', '\x80', 'w', '\xE5',
  '3', '\x7', '\xB8', '\x5C', '\x2E', 'H', '\x92', '\x4',
  '\x87', '\xC3', '\x81', '\x40', '\x20', '\x40', 'g', '\x98',
  '\xE9', '6', '\x1A', '\xA6', 'g', '\x15', '\x4', '\xE3',
  '\xD7', '\xC8', '\xBD', '\x15', '\xE1', 'i', '\xB7', 'C',
  '\xAB', '\xEA', 'x', '\x2F', 'j', 'X', '\x92', '\xBB',
  '\x18', '\x20', '\x9F', '\xCF', '3', '\xC3', '\xB8', '\xE9',
  'N', '\xA7', '\xD3', 'l', 'J', '\x0', 'i', '6',
  '\x7C', '\x8E', '\xE1', '\xFE', 'V', '\x84', '\xE7', '\x3C',
  '\x9F', 'r', '\x2B', '\x3A', 'B', '\x7B', '7', 'f',
  'w', '\xAE', '\x8E', '\xE', '\xF3', '\xBD', 'R', '\xA9',
  'd', '\x2', 'B', '\xAF', '\x85', '2', 'f', 'F',
  '\xBA', '\xC', '\xD9', '\x9F', '\x1D', '\x9A', 'l', '\x22',
  '\xE6', '\xC7', '\x3A', '\x2C', '\x80', '\xEF', '\xC1', '\x15',
  '\x90', '\x7', '\x93', '\xA2', '\x28', '\xA0', 'S', 'j',
  '\xB1', '\xB8', '\xDF', '\x29', '5', 'C', '\xE', '\x3F',
  'X', '\xFC', '\x98', '\xDA', 'y', 'j', 'P', '\x40',
  '\x0', '\x87', '\xAE', '\x1B', '\x17', 'B', '\xB4', '\x3A',
  '\x3F', '\xBE', 'y', '\xC7', '\xA', '\x26', '\xB6', '\xEE',
  '\xD9', '\x9A', '\x60', '\x14', '\x93', '\xDB', '\x8F', '\xD',
  '\xA', '\x2E', '\xE9', '\x23', '\x95', '\x29', 'X', '\x0',
  '\x27', '\xEB', 'n', 'V', 'p', '\xBC', '\xD6', '\xCB',
  '\xD6', 'G', '\xAB', '\x3D', 'l', '\x7D', '\xB8', '\xD2',
  '\xDD', '\xA0', '\x60', '\x83', '\xBA', '\xEF', '\x5F', '\xA4',
  '\xEA', '\xCC', '\x2', 'N', '\xAE', '\x5E', 'p', '\x1A',
  '\xEC', '\xB3', '\x40', '9', '\xAC', '\xFE', '\xF2', '\x91',
  '\x89', 'g', '\x91', '\x85', '\x21', '\xA8', '\x87', '\xB7',
  'X', '\x7E', '\x7E', '\x85', '\xBB', '\xCD', 'N', 'N',
  'b', 't', '\x40', '\xFA', '\x93', '\x89', '\xEC', '\x1E',
  '\xEC', '\x86', '\x2', 'H', '\x26', '\x93', '\xD0', 'u',
  '\x1D', '\x7F', '\x9', '2', '\x95', '\xBF', '\x1F', '\xDB',
  '\xD7', 'c', '\x8A', '\x1A', '\xF7', '\x5C', '\xC1', '\xFF',
  '\x22', 'J', '\xC3', '\x87', '\x0', '\x3', '\x0', 'K',
  '\xBB', '\xF8', '\xD6', '\x2A', 'v', '\x98', 'I', '\x0',
  '\x0', '\x0', '\x0', 'I', 'E', 'N', 'D', '\xAE',
  'B', '\x60', '\x82',
};//favicon图片,参考其他github直接拷贝的．

void Http_conn::initread(){
	pos=0;
	inbuffer="";
}

void Http_conn::initwrite(){
	outbuffer="";
	path="";
	header.clear();
}

Http_conn::Http_conn(SP_Channel Channel)
:	channel(Channel),
	storage("page/")
{
	initread();
	initwrite();
	channel->setReadhandler(bind(&Http_conn::parse,this));
	channel->setWritehandler(bind(&Http_conn::send,this));
}

Http_conn::~Http_conn(){
	
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
	int readsum=readn(channel->getFd(),inbuffer);
	if(readsum<0){
		perror("read error");
		parsestate=PARSE_ERROR;
		initread();
		return;
	}
	else if(!readsum){
		channel->setDeleted(true);
		channel->getLoop()->addTimer(channel,0);
		return;
	}
	if(parseMethod()==PARSE_METHOD_ERROR){
		perror("parse method error");
		parsestate=PARSE_ERROR;
		initread();
		return;
	}
	if(parseHeader()==PARSE_HEADER_ERROR){
		perror("parse header error");
		parsestate=PARSE_ERROR;
		initread();
		return;
	}
	initread();
	channel->setRevents(EPOLLOUT|EPOLLET);
	channel->getLoop()->updatePoller(channel);
}

void Http_conn::send(){
	if(METHOD_POST==method){

	}
	else if(METHOD_GET==method){
		if(HTTP_11==version&&header.find("Connection")!=header.end()&&("Keep-Alive"==header["Connection"]||"keep-alive"==header["Connection"])){
			outbuffer="HTTP/1.1 200 OK\r\n";
			outbuffer+=string("Connection: Keep-Alive\r\n")+"Keep-Alive: timeout="+to_string(DEFAULT_KEEP_ALIVE_TIME)+"\r\n";
			channel->getLoop()->addTimer(channel,DEFAULT_KEEP_ALIVE_TIME);
		}
		else{
			outbuffer="HTTP/1.0 200 OK\r\n";
			channel->getLoop()->addTimer(channel,0);
		}
		int dot_pos=path.find('.');
		string filetype;
		if(string::npos==dot_pos)
			filetype=Mimetype::getMime("default");
		else
			filetype=Mimetype::getMime(path.substr(dot_pos));
		if(path=="favicon.ico"){
			outbuffer += "Content-Type: image/png\r\n";
            outbuffer += "Content-Length: " + to_string(sizeof favicon) + "\r\n";
            outbuffer += "Server: WWQ's Web Server\r\n";
            outbuffer += "\r\n";
            outbuffer += string(favicon, favicon + sizeof favicon);;
		}
		else{
			struct stat sbuf;
			if(stat((storage+path).c_str(),&sbuf)<0){
				perror("no file");
				parsestate=PARSE_ERROR;
				return;
			}
			outbuffer += "Content-Type: " + filetype + "\r\n";
			outbuffer += "Content-Length: " + to_string(sbuf.st_size) + "\r\n";
        	outbuffer += "Server: WWQ's Web Server\r\n";
			outbuffer += "\r\n";
			int src_fd=open((storage+path).c_str(),O_RDONLY,0);
			if(src_fd<0){
				perror("open file failed");
				return;
			}
			char *src_addr=(char *)mmap(NULL,sbuf.st_size,PROT_READ,MAP_PRIVATE,src_fd,0);
			close(src_fd);
			outbuffer+=string(src_addr,src_addr+sbuf.st_size);
			munmap(src_addr,sbuf.st_size);
		}
	}
	printf("write fd=%d\n",channel->getFd());
	const char *buffer=outbuffer.c_str();
	if(!writen(channel->getFd(),buffer,outbuffer.length()))
		perror("writen error");
	initwrite();
	channel->setRevents(EPOLLIN|EPOLLET);
	channel->getLoop()->updatePoller(channel);
}
