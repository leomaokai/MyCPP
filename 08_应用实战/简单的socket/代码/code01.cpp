//code01.cpp code_tree
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<assert.h>

#define BUFFER_SIZE 1024

int main()
{
	//第一步:创建服务端的socket
	int sockfd=socket(PF_INET,SOCK_STREAM,0);
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
	struct sockaddr_in client;
	socklen_t clientlen=sizeof(client);
	int connfd=accept(sockfd,(struct sockaddr*)&client,&clientlen);
	assert(connfd!=-1);
	printf("connected with ip %s\n",inet_ntoa(client.sin_addr));
	
	//第五步:与客户端通信
	char buffer[BUFFER_SIZE];
	while(1)
	{
		memset(buffer,0,BUFFER_SIZE);
		ret=recv(connfd,buffer,BUFFER_SIZE-1,0);
		if(ret<=0)
		{
			printf("ret=%d\n",ret);
			break;
		}
		printf("ret=%d,recv:%s\n",ret,buffer);
		
		strcpy(buffer,"成功接收");
		ret=send(connfd,buffer,strlen(buffer),0);
		if(ret<=0)
			break;
	}

	//第六步:关闭连接
	close(sockfd);
	close(connfd);
}	
