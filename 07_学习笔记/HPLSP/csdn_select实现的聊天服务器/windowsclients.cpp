//Client.cpp
#include <winsock2.h>
#include <stdio.h>
#include <windows.h>
//引入静态链接库
#pragma comment(lib,"ws2_32.lib")
//缓冲区大小
#define BUFFER_SIZE  4096
//用来修改用户姓名的命令
const char* CMD_NAME="name";
//用来退出系统的命令
const char* CMD_BYE="bye";
//负责接收数据的线程
DWORD WINAPI ReceiveThreadProc( LPVOID lpParameter);
int main(int argc, char* argv[]){
	//判断是否输入了IP地址和端口号
	if(argc!=3){
		printf("Usage: %s IPAddress PortNumber/n",argv[0]);
		exit(-1);
	}
	//把字符串的IP地址转化为u_long
	unsigned long ip;
	if((ip=inet_addr(argv[1]))==INADDR_NONE){
		printf("不合法的IP地址：%s",argv[1]);
		exit(-1);
	}
	//把端口号转化成整数
	short port;
	if((port = atoi(argv[2]))==0){
		printf("端口号有误！");
		exit(-1);
	}
	printf("Connecting to %s:%d....../n",inet_ntoa(*(in_addr*)&ip),port);
	WSADATA wsa;
	//初始化套接字DLL
	if(WSAStartup(MAKEWORD(2,2),&wsa)!=0){
		printf("套接字初始化失败!");
		exit(-1);
	}
	//创建套接字
	SOCKET sock;
	if((sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==INVALID_SOCKET){
		printf("创建套接字失败！");
		exit(-1);
	}
	struct sockaddr_in serverAddress;
	memset(&serverAddress,0,sizeof(sockaddr_in));
	serverAddress.sin_family=AF_INET;
	serverAddress.sin_addr.S_un.S_addr = ip;
	serverAddress.sin_port = htons(port);
	//建立和服务器的连接
	if(connect(sock,(sockaddr*)&serverAddress,sizeof(serverAddress))==SOCKET_ERROR){
		printf("建立连接失败！");
		exit(-1);
	}
	//创建从服务器接收数据的线程
	DWORD threadId;
	CreateThread(NULL,0,ReceiveThreadProc,&sock,0,&threadId);
	printf(">");
	char buf[BUFFER_SIZE];
	while(1){
		//从控制台读取一行数据
		gets(buf);
		printf(">");
		
		//发送给服务器
	   if(send(sock,buf,strlen(buf),0)==SOCKET_ERROR){
			printf("发送数据失败！");
			exit(-1);
		}
	
	}
	//清理套接字占用的资源
	WSACleanup();
	return 0;
}
DWORD WINAPI ReceiveThreadProc( LPVOID lpParameter){
	SOCKET s = *(SOCKET*)lpParameter;
	char receiveBuf[BUFFER_SIZE];
	int bytes;
	while(1){
	   	if((bytes=recv(s,receiveBuf,sizeof(receiveBuf),0))==SOCKET_ERROR){
			printf("接收数据失败!/n");
			exit(-1);
		}
		if(bytes==0){
			printf("server is down./n");
			exit(-1);
		}
		receiveBuf[bytes]='/0';
		//如果用户输入了“bye”
		if(strcmp(receiveBuf,CMD_BYE)==0){
			closesocket(s);
			exit(0);
		}
		printf("/n%s/n>",receiveBuf);
	}
}