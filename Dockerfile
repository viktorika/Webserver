FROM alpine

ENV INSTALL_PATH=/opt/

COPY ./src $INSTALL_PATH

RUN apk add g++ make \
	&& make -C $INSTALL_PATH 
	
# FROM alpine
EXPOSE 8080
VOLUME /opt/page/
# ENV INSTALL_PATH=/opt/
WORKDIR $INSTALL_PATH 
# COPY --from=0 $INSTALL_PATH/WebServer .
CMD ./WebServer
