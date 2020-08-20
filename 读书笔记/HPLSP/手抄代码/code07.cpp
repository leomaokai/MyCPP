#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<string.h>
#include<netdb.h>
#define BUFFER_SIZE 128
class Server
{
public:
	int m_listenfd;
	int m_connfd;
public:
	Server();
	bool initserver();
	bool Accept();
	int Recv(void* buf,const int buflen);
	int Send(const void* buf,const int buflen);
	~Server();
};
void sig_handler(int sig);
void* another(void* arg);
int main()
{
	for(int i=0;i<50;i++) signal(i,SIG_IGN);
	signal(SIGINT,sig_handler);
	signal(SIGTERM,sig_handler);
	
	Server server;
	if(server.initserver()==false)
		return 1;
	while(1)
	{
		if(server.Accept()==false)
			continue;
		pthread_t pthid;
		if(pthread_create(&pthid,NULL,another,(void*)((long)server.m_connfd))!=0)
			return 1;
		printf("客户与服务线程连接\n");
		pthread_detach(pthid);
	}
	return 0;
}

Server::Server():m_listenfd(0),m_connfd(0)
{
	printf("构造函数调用\n");
}
Server::~Server()
{
	printf("析构函数调用\n");
	if(m_listenfd!=0) close(m_listenfd);
	if(m_connfd!=0) close(m_connfd);
}
	
bool Server::initserver()
{
	m_listenfd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in address;
	memset(&address,0,sizeof(address));
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=htonl(INADDR_ANY);
	address.sin_port=htons(54321);
	if(bind(m_listenfd,(struct sockaddr*)&address,sizeof(address))!=0)
	{
		close(m_listenfd);m_listenfd=0;return false;
	}
	if(listen(m_listenfd,5)!=0)
	{
		close(m_listenfd);m_listenfd=0;return false;
	}
	return true;
}
bool Server::Accept()
{
	if((m_connfd=accept(m_listenfd,0,0))<=0)
		return false;
	return true;
}
int Server::Recv(void* buf,const int buflen)
{
	return recv(m_connfd,buf,buflen,0);
}
int Server::Send(const void* buf,const int buflen)
{
	return send(m_connfd,buf,buflen,0);
}

void sig_handler(int sig)
{
	printf("收到信号:%d\n",sig);
	exit(0);
}
void* another(void* arg)
{
	int connfd=(long) arg;
	char buf[BUFFER_SIZE];
	
	while(1)
	{
		memset(&buf,0,BUFFER_SIZE);
		if(recv(connfd,buf,BUFFER_SIZE,0)<=0)
			break;
		printf("成功接收到数据\n");
		memset(&buf,0,BUFFER_SIZE);
		strcpy(buf,"成功接收");
		if(send(connfd,buf,strlen(buf),0)<=0)
			break;
	}
	printf("断开连接\n");

	close(connfd);
	pthread_exit(0);
}

