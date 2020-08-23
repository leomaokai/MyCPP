# I/O复用--select



I/O复用使得程序能同时监听多个文件描述符,对提高程序的性能至关重要.

Linux实现I/O复用的系统调用主要有select、poll、epoll。

# select基本用法

```cpp
//code10.cpp code_tree
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<assert.h>
#include<sys/select.h>
#include<signal.h>
#define MAX_USER 2
#define BUFFER_SIZE 64

void sig_handler(int sig);
int fds[MAX_USER]; 
int sockfd=0;
int main()
{
	signal(SIGINT,sig_handler);
	//第一步:创建服务端的socket
	sockfd=socket(PF_INET,SOCK_STREAM,0);
	assert(socket>=0);
	
	//第二步:绑定地址与端口号
	int ret=0;
	struct sockaddr_in address;
	memset(&address,0,sizeof(address));
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=htonl(INADDR_ANY);
	address.sin_port=htons(54321);
	ret=bind(sockfd,(struct sockaddr*)&address,sizeof(address));
	assert(ret!=-1);
	
	//第三步:把socket设置为监听模式
	ret=listen(sockfd,5);
	assert(ret!=-1);

	//第四步:接受客户端连接
	int fdmax=0;
	for(int i=0;i<MAX_USER;++i)
	{
		struct sockaddr_in client;
		socklen_t clientlen=sizeof(client);
		fds[i]=accept(sockfd,(struct sockaddr*)&client,&clientlen);
		printf("connected with ip %s\n",inet_ntoa(client.sin_addr));
		if(fds[i]>fdmax)
			fdmax=fds[i];
	}
	
	//第五步:与客户端通信
	fd_set read_fds;
	char buffer[BUFFER_SIZE];
	while(1)
	{
		FD_ZERO(&read_fds);
		for(int i=0;i<2;++i)
			FD_SET(fds[i],&read_fds);
		select(fdmax+1,&read_fds,NULL,NULL,NULL);
		for(int i=0;i<2;++i)
		{
			if(FD_ISSET(fds[i],&read_fds))
			{
				memset(buffer,0,BUFFER_SIZE);
				ret=recv(fds[i],buffer,BUFFER_SIZE,0);
				if(ret>0)
				{
					printf("recv the data from the %d user\n",i+1);
				}
				else
					continue;
			}
		}
	}
}
void sig_handler(int sig)
{
	printf("收到信号 %d \n",sig);
	for(int i=0;i<MAX_USER;++i)
	{
		if(fds[i]!=0)
			close(fds[i]);
	}
	if(sockfd!=0)
	{
		close(sockfd);
		printf("close\n");
	}
	exit(0);
}

```

这一段代码中select同时监听多个fd的可读事件.

select第一个参数是监听文件描述符总数,通常是监听所有文件描述符中的最大值+1.

第二第三第四个参数是fd_set结构指针类型,分别指向可读,可写,和异常事件对应的文件描述符集合.

第五个参数设置select函数超时时间.

**原理:**

将事件集合交给内核,由内核判断是否就绪

**缺点:**

* 事件集合默认大小1024
* 事件集合不可重用
* 用户态<一>内核态
* 事件就绪仍要O(n)遍历