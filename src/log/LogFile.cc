#include "LogFile.h"

LogFile::LogFile(const std::string &Basename,int FlushEveryN)
:	basename(Basename),
	flushEveryN(FlushEveryN),
	count(0),
	file(new FileUtil(basename))
{

}

LogFile::~LogFile(){

}

void LogFile::append(const char *logline,int len){
	append_unlocked(logline,len);
}

void LogFile::flush(){
	file->flush();
}

bool LogFile::rollFile(){
	
}

void LogFile::append_unlocked(const char *logline,int len){
	file->append(logline,len);
	++count;
	if(flushEveryN==count){
		count=0;
		file->flush();
	}
}
