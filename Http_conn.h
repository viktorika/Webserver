#pragma once

#include "Packet.h"
#include "Mimetype.h"
#include "Reactor/EventLoop.h"
#include <string>
#include <unordered_map>
#include <iostream>
#include <sys/mman.h>

using namespace std;
#define DEFAULT_KEEP_ALIVE_TIME 20000

enum METHOD{METHOD_GET,METHOD_POST};
enum HTTPVERSION{HTTP_10,HTTP_11};
enum METHODSTATE{PARSE_METHOD_ERROR,PARSE_METHOD_SUCCESS};
enum HEADERSTATE{PARSE_HEADER_ERROR,PARSE_HEADER_SUCCESS};
enum PARSESTATE{PARSE_SUCCESS,PARSE_ERROR};

class Channel;
typedef shared_ptr<Channel> SP_Channel;

class Http_conn{
private:
	SP_Channel channel;
	int pos;
	string inbuffer;
	string outbuffer;
	string path;
	METHOD method;
	HTTPVERSION version;
	PARSESTATE parsestate;
	unordered_map<string,string>header;
	METHODSTATE parseMethod();
	HEADERSTATE parseHeader();
	//CONTENTSTATE parseContent();
	bool Read(string &msg,string str);
	void init();
public:
	Http_conn(SP_Channel channel);
	~Http_conn();
	void setsockfd(int sockfd);
	void parse();
	void send();	
};

typedef shared_ptr<Http_conn> SP_Http_conn;
