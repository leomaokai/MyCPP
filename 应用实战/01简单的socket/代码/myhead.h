#ifndef MYHEAD_H
#define MYHEAD_H

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>
#include<fcntl.h>
#include<errno.h>
#include<poll.h>
#include<sys/epoll.h>

#define BUFFER_SIZE 128
//服务端类
class Server
{
public:
    int m_listenfd;
    int m_connfd; 
public:
    Server();
    
    bool InitServer(int port);
    bool Accept();
    int  Send(const void *buf,const int buflen);
    int  Recv(void *buf,const int buflen);
 
   ~Server();
};
//客户端类
class Client
{
public:
    int m_sockfd;
public:
    Client();
    
    bool CliToSer(const char* ip,const int port);
    int  Send(const void *buf,const int buflen);
    int  Recv(void *buf,const int buflen);
    
    ~Client();
};
//将文件描述符设置为非阻塞
int setnonblocking(int fd);

#endif
