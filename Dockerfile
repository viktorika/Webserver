FROM alpine

ENV INSTALL_PATH=/opt/

COPY ./src $INSTALL_PATH

RUN apk add g++ make \
	&& make -C $INSTALL_PATH 
	
CMD cd $INSTALL_PATH  \
	&& $INSTALL_PATH/WebServer
