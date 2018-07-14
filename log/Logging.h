#pragma once

#include "AsyncLogging.h"
#include <sys/time.h>
#include "FixedBuffer.h"

class Impl{
public:
	Impl(const char *filename,int line);
	void formatTime();
	std::string getBaseName();
	LogStream& stream();
	int getLine();	

private:
	LogStream stream_;
	int line;
	std::string basename;
};

class Logger{
private:
	Impl impl;
	static std::string logFileName;

public:
	Logger(const char *filename,int line);
	~Logger();
	LogStream& stream();
	static void setLogFileName(std::string fileName);
	static std::string getLogFileName();
};

#define LOG Logger(__FILE__,__LINE__).stream()
