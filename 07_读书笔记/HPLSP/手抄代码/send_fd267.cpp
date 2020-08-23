#include<sys/socket.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

static const int CONTROL_LEN=CMSG_LEN(sizeof(int));
void send_fd(int fd,int fd_to_send)
{
	struct iovec iov[1];
	struct msghdr msg;
	char buf[0];
	
	iov[0].iov_base=buf;
	iov[0].iov_len=1;
	msg.msg_name=NULL;
	msg.msg_namelen=0;
	msg.msg_iov=iov;
	msg.msg_iovlen=1;

	cmsghdr cm;
	cm.cmsg_len=CONTROL_LEN;
	cm.cmsg_level=SOL_SOKCET;
	cm.cmsg_type=SCM_RIGHTS;
	
