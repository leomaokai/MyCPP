#include"myhead.h"

Server::Server():m_listenfd(0),m_connfd(0)
{
	printf("构造函数调用\n");
}
Server::~Server()
{
	printf("析构函数调用\n");
    if(m_listenfd!=0)	
        close(m_listenfd);
    if(m_connfd!=0)		
        close(m_connfd);
}

bool Server::InitServer(int port)
{
    m_listenfd=socket(AF_INET,SOCK_STREAM,0);
 
    struct sockaddr_in servaddr; 
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(port);
    
    if(bind(m_listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr))!=0)
    { 
        close(m_listenfd);
        m_listenfd=0; 
        return false; 
    }
    
    if (listen(m_listenfd,5) != 0 )
    { 
        close(m_listenfd);
     	m_listenfd=0;
    	return false; 
    }
    
    return true;
}

bool Server::Accept()
{
	struct sockaddr_in client;
	socklen_t clientlen=sizeof(client);
    if((m_connfd=accept(m_listenfd,(struct sockaddr*)&client,&clientlen))<=0)
        return false;
    return true;
}

int Server::Send(const void* buf,const int buflen)
{
    return send(m_connfd,buf,buflen,0);
}
int Server::Recv(void* buf,const int buflen)
{
    return recv(m_connfd,buf,buflen,0);
}


Client::Client():m_sockfd(0){}
Client::~Client()
{
    if(m_sockfd!=0)
        close(m_sockfd);
}

bool Client::CliToSer(const char* ip,const int port)
{
    m_sockfd = socket(AF_INET,SOCK_STREAM,0);
    
    struct sockaddr_in servaddr;
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    inet_pton(AF_INET,ip,&servaddr.sin_addr);
 
    if (connect(m_sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))!=0)
    {
        close(m_sockfd);
        m_sockfd=0; 
        return false; 
    }
 
    return true;
}

int Client::Send(const void* buf,const int buflen)
{
    return send(m_sockfd,buf,buflen,0);
}
int Client::Recv(void* buf,const int buflen)
{
    return recv(m_sockfd,buf,buflen,0);
}

int setnonblcoking(int fd)
{
	int old_option=fcntl(fd,F_GETFL);
	int new_option=old_option | O_NONBLOCK;
	fcntl(fd,F_SETFL,new_option);
	return old_option;
}
