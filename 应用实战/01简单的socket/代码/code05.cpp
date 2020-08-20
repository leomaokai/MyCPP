#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<assert.h>
#include<signal.h>

#define BUFFER_SIZE 1024

class Server
{
private:
    int m_listenfd; 
    int m_connfd;  
public:
    Server();
    
    bool InitServer(int port); 
    bool Accept();  	
    int  Send(const void *buf,const int buflen);
    int  Recv(void *buf,const int buflen);
    void Closelistenfd();
    void Closeconnfd();	
 
   ~Server();
};

int main()
{
    Server server;
    signal(SIGCHLD,SIG_IGN);
    
    if(server.InitServer(54321)==false)
        return -1;
    while(1)
    {
        if(server.Accept()==false)
  	    	  return -1;
  	  	printf("connect ok\n");
        if(fork()>0)
        {
            server.Closeconnfd();
            continue;
        }
        
    	server.Closelistenfd();
        printf("子进程与客户端连接\n");
        
    	char buffer[BUFFER_SIZE];
    	while(1)
   		{
        	memset(buffer,0,BUFFER_SIZE);
        	if(server.Recv(buffer,BUFFER_SIZE-1)<=0)
            	break;
        	printf("接收: %s\n",buffer);
        
        	strcpy(buffer,"成功接收");
        	if(server.Send(buffer,strlen(buffer))<=0)
            	break;
        	printf("发送: %s\n",buffer);
    	}
    	
    	printf("连接断开\n");
        return 0;	//或exit(0),子进程退出
    }
}

Server::Server():m_listenfd(0),m_connfd(0){}
Server::~Server()
{
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
    if((m_connfd=accept(m_listenfd,0,0))<=0)
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
void Server::Closelistenfd()
{
    close(m_listenfd);
    m_listenfd=0;
}
void Server::Closeconnfd()
{
    close(m_connfd);
    m_connfd=0;
}
