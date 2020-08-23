#include"apue.h"
#include<netdb.h>
#include<errno.h>
#include<syslog.h>
#include<sys/socket.h>

#define BUFLEN 128		
#define MAXADDRLEN 256

#ifndef HOST_NAME_MAX	//34主机名最大长度限制
#define HOST_NAME_MAX 256
#endif

extern int initserver(int,const struct sockaddr*,socklen_t,int);//490初始化一个套接字
void serve(int sockfd)
{
	int n;
	socklen_t alen;	
	FILE *fp;
	char buf[BUFLEN];
	char abuf[MAXADDRLEN];
	struct sockaddr *addr=(struct sockaddr *)abuf;//478地址格式
	set_cloexec(sockfd);	//386关闭标志
	for(;;){
		alen=MAXADDRLEN;
		//493使用recvfrom来得到数据发送者的源地址
		if((n=recvfrom(sockfd,buf,BUFLEN,0,addr,&alen))<0){
			syslog(LOG_ERR,"ruptimed:recvfrom error:%s",strerror(errno));//378出错记录
			exit(1);
		}
		//436popen和pclose创建管道读取数据
		if((fp=popen("/usr/bin/uptime","r"))==NULL){
			sprintf(buf,"error:%s\n",strerror(errno));//127sprintf将格式化字符送入数组
			sendto(sockd,buf,strlen(buf),0,addr,alen);//492sento发送数据
		}else{
			if(fgets(buf,BUFLEN,fp)!=NULL)//122fgets每次输入一行
				sendto(sockfd,buf,strlen(buf),0,addr,alen);
			pclose(fp);
		}
	}
}
int main(int argc,char *argv[])
{
	struct addrinfo *ailist,*aip;//482addrinfo结构
	struct addrinfo hint;
	int sockfd,err,n;
	char *host;
	if(argc!=1)
		err_quit("usage:ruptimed");
	if((n=sysconf(_SC_HOST_NAME_MAX)<0)//33sysconf标识系统限制
		n=HOST_NAME_MAX;
	if((host=malloc(n))==NULL)//165malloc存储空间分配
		err_sys("malloc error");
	if(gethostname(host,n)<0)//150gethostname返回主机名
		err_sys("gethostname error");
	daemonize("ruptimed");//375daemonize初始化守护进程
	memset(&hint,0,sizeof(hint));//memset内存空间初始化
	hint.ai_flags=AI_CANONNAME;
	hint.ai_socktype=SOCK_DGRAM;
	hint.ai_canonname=NULL;
	hint.ai_addr=NULL;
	hint.ai_next=NULL;
	//482getaddrinfo函数将一个主机名和一个服务名映射到一个地址
	if((err=getaddrinfo(host,"ruptime",&hint,&ailist))!=0){
		syslog(LOG_ERR,"ruptimed:getaddrinfo error:%s",gai_strerror(err));
		exit(1);
	}
	for(aip=ailist;aip!=NULL;aip=aip->ai_next){
		if((sockfd=initserver(SOCK_DGRAM,aip->ai_addr,aip->ai_addrlrn,0))>=0){
			serve(sockfd);
			exit(0);
		}
	}
	exit(1);
}