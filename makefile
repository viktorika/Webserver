Webserver:main.o Server.o Http_conn.o Mimetype.o Packet.o
	g++ -std=c++11 -o Webserver main.o Server.o Http_conn.o Mimetype.o Packet.o -lpthread	

main.o:main.cc
	g++ -std=c++11 -g -c main.cc

Server.o:Server.cc Server.h
	g++ -std=c++11 -g -c Server.cc

Http_conn.o:Http_conn.cc Http_conn.h
	g++ -std=c++11 -g -c Http_conn.cc

Mimetype.o:Mimetype.cc Mimetype.h
	g++ -std=c++11 -g -c Mimetype.cc

Packet.o:Packet.cc Packet.h
	g++ -std=c++11 -g -c Packet.cc
