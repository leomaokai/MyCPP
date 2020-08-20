#include"myhead2.h"


myshms::myshms():m_shmid(0),shmptr(NULL){}
bool myshms::getshm()
{
	if((m_shmid=shmget((key_t)0x5000,MAXUSERS*BUFFER_SIZE,0666|IPC_CREAT))==-1)
		return false;
	shmptr=(char*)shmat(m_shmid,0,0);
	return true;
}
myshms::~myshms()
{
	shmdt(shmptr);
	if(shmctl(m_shmid,IPC_RMID,0)==-1)
		printf("del shm failure\n");
	else
		printf("del shm ok\n");
}

servers::servers()
{
	printf("servers 构造函数\n");
	m_listenfd=0;
	m_connfd=0;
	client=0;
}
servers::~servers()
{
	prinft("servers 析构函数\n");
	if(m_listenfd!=0)
	{
		close(m_listenfd);
		m_listenfd=0;
	}
	if(m_connfd!=0)
	{
		close(m_connfd);
		m_connfd=0;
	}
	delete [] client;
}
void servers::setsig()
{
	m_epollfd=epoll_create(5);
	int ret=socketpair(PF_UNIX,SOCK_STREAM,0,sig_pipefd);
	setnonblocking(sig_pipefd[1]);
	addfd(m_epollfd,sig_pipefd[0];
	signal(SIGCHLD,sig_handler);
	signal(SIGTERM,sig_handler);
	signal(SIGTERM,sig_handler);
	signal(SIGPIPE,SIG_IGN);
}
void servers::run_child()
{
	setsig();
	int pipefd=client[m_idx].m_pipefd[1];
	addfd(m_epollfd,pipefd);
	epoll_event events[MAXEVET];
	int number=0;
	int ret=0;
	int connfd=accept(m_listenfd,0,0);
	addfd(m_epollfd,connfd);
	while(!m_stop)
	{
		number=epoll_wait(m_epollfd,events,MAXEVENT,-1);
		if((number<0)&&(errno!=EINTR))
		{
			printf("epoll failure\n");
			break;
		}
	
		for(int i=0;i<number;++i)
		{
			int sockfd=events[i].data.fd;
			if((sockfd==pipefd)&&(events[i].events & EPOLLIN))
			{
				int clientbuf=0;
				ret=recv(sockfd,(char*)clientbuf,sizeof(clientbuf),0);
				if(ret>0)
				{
					send(connfd,ptrshm+clientbuf*BUFFER_SIZE,BUFFER_SIZE,0);
				}
				else
					m_stop=true;;
			}
			else if((sockfd==connfd)&&(events[i].events & EPOLLIN))
			{
				memset(ptrshm+m_idx*BUFFER_SIZE,0,BUFFER_SIZE);
				ret=recv(connfd,ptrshm+m_idx*BUFFER_SIZE,BUFFER_SIZE-1,0);
				if(ret>0)
				{
					sned(pipefd,(char*)&idx,sizeof(idx),0);
				}
				else
					m_stop=true;
			}
			else if((sockfd==sig_pipefd[0])&&(events[i].events & EPOLLIN))
			{
				int sig;
				char signals[1024];
				ret=recv(sig_pipefd[0],signals,sizeof(signals),0);
				if(ret<=0)
					continue;
				else
				{
					for(int j=0;j<ret;++j)
					{
						switch(signals[j])
						{
							case SIGCHLD:
								signal(	
						
			
