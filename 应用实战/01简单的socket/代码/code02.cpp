//code02.cpp code_tree
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define BUFFER_SIZE 1024

int main()
{
	const char* ip="192.168.64.128";
	
	//第一步:创建客户端socket
	int sockfd=socket(PF_INET,SOCK_STREAM,0);
	assert(sockfd>=0);
	
	//第二步:向服务器发起连接
	int ret=0;
	struct sockaddr_in server;
	memset(&server,0,sizeof(server));
	server.sin_family=AF_INET;
	inet_pton(AF_INET,ip,&server.sin_addr);
	server.sin_port=htons(54321);
	ret=connect(sockfd,(struct sockaddr*)&server,sizeof(server));
	sleep(10);
	if(ret!=0)
	{
		printf("connection failed\n");
		close(sockfd);
		return -1;
	}
		
	//第三步:与服务端通信
	char buffer[BUFFER_SIZE];
	for(int i=0;i<3;++i)
	{
		memset(buffer,0,BUFFER_SIZE);
		strcpy(buffer,"数据");
		ret=send(sockfd,buffer,strlen(buffer),0);
		if(ret<=0)
			break;
		printf("ret=%d,发送%d次%s\n",ret,i+1,buffer);
		sleep(10);
	}
	
	//第四步:关闭socket
	close(sockfd);
}
