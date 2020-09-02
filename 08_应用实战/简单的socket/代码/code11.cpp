//code11.cpp code_tree
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<assert.h>
#include<poll.h>
#include<signal.h>
#define MAX_USER 2
#define BUFFER_SIZE 64

void sig_handler(int sig);
pollfd fds[MAX_USER]; 
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
		fds[i].fd=accept(sockfd,(struct sockaddr*)&client,&clientlen);
		printf("connected with ip %s\n",inet_ntoa(client.sin_addr));
		fds[i].events=POLLIN;
		fds[i].revents=0;	
	}
	
	//第五步:与客户端通信
	char buffer[BUFFER_SIZE];
	while(1)
	{
		poll(fds,2,-1);
		for(int i=0;i<2;++i)
		{
			if(fds[i].revents=POLLIN)
			{
				memset(buffer,0,BUFFER_SIZE);
				ret=recv(fds[i].fd,buffer,BUFFER_SIZE,0);
				if(ret>0)
					printf("recv the data from the %d user \n",i+1);
				else
					continue;
			}
		}
	}
}
void sig_handler(int sig)
{
	printf("recv sig %d \n",sig);
	close(sockfd);
	for(int i=0;i<2;++i)
	{
		if(fds[i].fd!=0)
		{
			close(fds[i].fd);
		}
	}
	exit(0);
}
	
