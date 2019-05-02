#include "Server.h"

Server::Server(const char * port,int threadnum)
:	loop(newElement<EventLoop>(),deleteElement<EventLoop>),
	serverchannel(newElement<Channel>(loop),deleteElement<Channel>),
	iothreadpool(newElement<ThreadpoolEventLoop>(threadnum),deleteElement<ThreadpoolEventLoop>)
{
	//ssl初始化
	if(getconf().getssl()){
		SSL_load_error_strings ();
		SSL_library_init ();
		ctx=SP_SSL_CTX(SSL_CTX_new(SSLv23_method()),SSL_CTX_free);
		int r = SSL_CTX_use_certificate_file(ctx.get(), getconf().getsslcrtpath().c_str(), SSL_FILETYPE_PEM);
		if(r<=0)
			LOG<<"ssl_ctx_use_certificate_file failed";
		r = SSL_CTX_use_PrivateKey_file(ctx.get(), getconf().getsslkeypath().c_str(), SSL_FILETYPE_PEM);
		if(r<=0)
			LOG<<"ssl_ctx_user_privatekey_file failed";
		r = SSL_CTX_check_private_key(ctx.get());
		if(!r)
			LOG<<"ssl_ctx_check_private_key failed";
	}
	listenfd=tcp_listen(NULL,port,NULL);
	setnonblocking(listenfd);
	serverchannel->setFd(listenfd);
}

Server::~Server(){
	Close(listenfd);
}

void Server::ssl_hand_shake(WP_Channel wpchannel){
	SP_Channel channel=wpchannel.lock();
	int result=SSL_do_handshake(channel->getssl().get());
	int connfd=channel->getFd();
	if(1==result){
		channel->setsslconnect(true);
		channel->setRevents(EPOLLIN|EPOLLET);
        SP_Http_conn connhttp(newElement<Http_conn>(channel),deleteElement<Http_conn>);            
		Httpmap[connfd]=move(connhttp);
		channel->getLoop().lock()->updatePoller(channel);
		return;
	}
	int error=SSL_get_error(channel->getssl().get(),result);
	if (SSL_ERROR_WANT_WRITE==error){
		channel->setRevents(EPOLLOUT);
		channel->getLoop().lock()->updatePoller(channel);
	}
    else if (SSL_ERROR_WANT_READ==error){
		channel->setRevents(EPOLLIN);
		channel->getLoop().lock()->updatePoller(channel);
	}
    else {
		LOG<<"ssl handshake error";
		channel->setDeleted(true);
        channel->getLoop().lock()->addTimer(channel,0);
    }
}

void Server::handleconn(){
	struct sockaddr_storage cliaddr;
	socklen_t clilen=sizeof(cliaddr);
	int connfd;
	while((connfd=Accept(listenfd,(SA *)&cliaddr,&clilen))>=0){
		LOG<<"accept fd="<<connfd;
		setnonblocking(connfd);
		SP_EventLoop nextloop=iothreadpool->getNextloop();
		SP_Channel connchannel(newElement<Channel>(nextloop),deleteElement<Channel>);
		connchannel->setFd(connfd);
		WP_Channel wpchannel=connchannel;
		connchannel->setClosehandler(bind(&Server::handleclose,this,wpchannel));
		if(getconf().getssl()){
			connchannel->setRevents(EPOLLIN);
			SP_SSL ssl(SSL_new(ctx.get()),SSL_free);
			SSL_set_fd(ssl.get(),connfd);
			SSL_set_accept_state(ssl.get());
			connchannel->setssl(ssl);
			connchannel->setsslconnect(false);
			connchannel->setReadhandler(bind(&Server::ssl_hand_shake,this,wpchannel));
		}
		else{
			connchannel->setRevents(EPOLLIN|EPOLLET);
			SP_Http_conn connhttp(newElement<Http_conn>(connchannel),deleteElement<Http_conn>);
			Httpmap[connfd]=move(connhttp);
		}
		nextloop->queueInLoop(bind(&EventLoop::addPoller,nextloop,move(connchannel)));
	}
}

void Server::start(){
	iothreadpool->start();
	serverchannel->setRevents(EPOLLIN|EPOLLET);
	serverchannel->setReadhandler(bind(&Server::handleconn,this));
	loop->addPoller(serverchannel);
	LOG<<"start";
	loop->loop();
}

void Server::handleclose(WP_Channel channel){
	SP_Channel spchannel=channel.lock();
	loop->queueInLoop(bind(&Server::deletemap,this,spchannel));
	spchannel->getLoop().lock()->removePoller(spchannel);
}

void Server::deletemap(SP_Channel channel){
	Httpmap.erase(channel->getFd());
}
