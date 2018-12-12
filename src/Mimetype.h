#pragma once

#include <map>
#include <pthread.h>

class Mimetype{
private:
	static pthread_once_t once_control;
	static std::map<std::string,std::string>mime;
	static void init();	
	Mimetype();
public:
	static std::string getMime(const std::string &suffix);
};
