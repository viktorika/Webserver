#include "Mimetype.h"

pthread_once_t Mimetype::once_control=PTHREAD_ONCE_INIT;
std::map<std::string,std::string> Mimetype::mime;

void Mimetype::init(){
    mime[".html"] = "text/html";
    mime[".avi"] = "video/x-msvideo";
    mime[".bmp"] = "image/bmp";
    mime[".c"] = "text/plain";
    mime[".doc"] = "application/msword";
    mime[".gif"] = "image/gif";
    mime[".gz"] = "application/x-gzip";
    mime[".htm"] = "text/html";
    mime[".ico"] = "image/x-icon";
    mime[".jpg"] = "image/jpeg";
    mime[".png"] = "image/png";
    mime[".txt"] = "text/plain";
    mime[".mp3"] = "audio/mp3";
    mime["default"] = "text/html";
}

Mimetype::Mimetype(){

}

std::string Mimetype::getMime(const std::string &suffix){
	pthread_once(&once_control,Mimetype::init);
	if(mime.find(suffix)==mime.end())
		return mime["default"];
	else
		return mime[suffix];
}
