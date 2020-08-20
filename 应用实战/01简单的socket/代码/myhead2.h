#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<epoll.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<signal.h>

#define BUFFER_SIZE 128
#define MAXUSERS 5
#define MAXEVENT 1024
class clients
{
public:
	clients():m_pid(-1){}

	pid_t m_pid;
	int m_pipefd[2];
};

class myshms
{
public:
	myshms();
	~myshms();
	bool getshm();
	char* shmptr;
private:
	int shmid;
};
static int counter=0;
static int*  process=new int [65536];
for(int i=0;i<65536;++i)
	process[i]=-1;
class servers
{
private:
	bool m_stop;
	int m_listenfd;
	int m_epollfd;
	clients* client;
	myshms myshm;
public:
	bool initserver();
	void setsig();
	servers();
	~servers();
	void run_child(int pid);
	void run_parent(int pid);
};
int setnonblocking(int fd)
{
	int old_option=fcntl(fd,F_GETFL);
	int new_option=old_option|O_NONBLOCK;
	fcntl(fd,F_SETFL,new_option);
	return old_option;
}
static int sig_pipefd[2];
void sig_handler(int sig)
{
	send(sig_pipefd[1],(char*)&sig,1,0);
}
void addfd(int epollfd,int fd)
{
	epoll_event event;
	event.data.fd=fd;
	event.events=EPOLLIN | EPOLLET;
	epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event);
	setnonblocking(fd);
}

