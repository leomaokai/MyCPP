/*server.c*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <pthread.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "MessageBuffer.h"
#include "Clients.h"
using namespace std;
#define SERVER_PORT 8000
#define BUFFER_SIZE 4096
#ifndef MAX_CLIENT
#define MAX_CLIENT 30
#endif
#ifndef NAME_LEN
#define NAME_LEN 50
#endif
MessageBuffer messageBuffer;
Clients clients;
void* ListenThread(void*);
void* RecvThread(void*);
void* SendThread(void*); 
void ProcessMessage(int sock,char buf[],int bufsize,int bytes);
bool toStop=false;
int main(int argc,char* argv[]) {
 
  if(argc!=2){
    printf("Usage: %s PortNumber/n",argv[0]);
    return -1;
  }
  unsigned short port;
  if((port = atoi(argv[1]))==0){
     printf("incorrect port number./n");
     return -1;
  }
  int s;
  struct sockaddr_in serverAddr;
 
  s = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
  if(s==-1){
    fprintf(stderr,"create socket failed./n");
    return -1;
  }
  bzero(&serverAddr,sizeof(struct sockaddr_in));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(port);
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  if(bind(s,(struct sockaddr*)&serverAddr,sizeof(serverAddr))==-1){
    fprintf(stderr,"bind socket to port %d failed./n",port);
    return -1;
  }
  if(listen(s,SOMAXCONN)==-1){
    fprintf(stderr,"listen failed./n");
    return -1;
  }
  printf("Server  is listening on ");
  char hostname[255];
  if(gethostname(hostname,sizeof(hostname))){
    printf("gethostname() failed./n");
    return -1;
  }
  struct hostent* pHost = gethostbyname(hostname);
  if(pHost){
      for(int i=0; pHost->h_addr_list[i]; i++){
         printf("%s ",inet_ntoa(*(in_addr*)pHost->h_addr_list[i]));
      }
  }
  printf("/nport: %d/n",port);
  pthread_t tListenId;
  if(pthread_create(&tListenId,NULL,ListenThread,&s)){
    printf("failed to create listen thread./n");
    return -1;
  }
  pthread_t tRecvId;
  if(pthread_create(&tRecvId,NULL,RecvThread,NULL)){
    printf("failed to create recv thread./n");
    return -1;
  }
  pthread_t tSendId;
  if(pthread_create(&tSendId,NULL,SendThread,NULL)){
    printf("failed to create send thread./n");
    return -1;
  }
  
  while(getchar()!='q');
  
  toStop = true;
  messageBuffer.toStop = true;
 
  pthread_join(tListenId,NULL);
  pthread_join(tRecvId,NULL);
  pthread_join(tSendId,NULL);
  close(s);
  int sock[MAX_CLIENT];
  int count = clients.GetAllSocket(sock,MAX_CLIENT);
  for(int i=0;i<count;i++){
    close(sock[i]);
  }
  
  printf("server stopped./n");
  
  return 0;
}
void* ListenThread(void*ps){
  int s=*(int*)ps;
  fd_set listenSet;
  int sock;
  struct sockaddr_in clientAddr;
  struct timeval timeout;
  while(!toStop){
     FD_ZERO(&listenSet);
     FD_SET(s,&listenSet);
     timeout.tv_sec = 5;
     timeout.tv_usec = 0;
     int ret = select(s+1,&listenSet,NULL,NULL,&timeout);
     if(toStop){
          printf("ListenThread: exit./n");
          return NULL;
     }
     if(ret==-1){
        printf("ListenThread: select() failed!/n");
     }else if(ret==0){
        printf("ListenThread: select() time out./n");
     }else{
        if(FD_ISSET(s,&listenSet)){
           socklen_t addrlen = sizeof(struct sockaddr_in);
           memset(&clientAddr,0,sizeof(struct sockaddr_in));
           if((sock=accept(s,(struct sockaddr*)&clientAddr,&addrlen))==-1){
               fprintf(stderr,"accept failed./n");
           }
           if(!clients.PutClient(sock,clientAddr)){
               printf("max client limited. MAX_CLIENT=%d/n",MAX_CLIENT);
               close(sock);
           }
           printf("accept a connection from %s:%u/n",
                   inet_ntoa(*(struct in_addr*)&(clientAddr.sin_addr.s_addr)),
                   ntohs(clientAddr.sin_port));
           printf("new socket is: %u/n",sock);
         }
     }
   }
   return NULL;
}
void* RecvThread(void*){
  fd_set readSet;
  int sock[MAX_CLIENT];
  char buf[BUFFER_SIZE];
  struct timeval timeout;
  while(!toStop){
    int count = clients.GetAllSocket(sock,MAX_CLIENT);
    if(count==0){
      sleep(2);
      if(toStop){
        printf("RecvThread: exit./n");
        return NULL;
      }
      continue;  
    }
    FD_ZERO(&readSet);
    int maxfd=0;
    for(int i=0;i<count;i++){
       printf("--%d",sock[i]);
       FD_SET(sock[i],&readSet);
       if(sock[i]>maxfd){
         maxfd = sock[i];
       }
    }
    printf("/n");
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;
    int ret = select(maxfd+1,&readSet,NULL,NULL,&timeout);
    if(toStop){
        printf("RecvThread: exit./n");
        return NULL;
    }
    if(ret==-1){
      printf("RecvThread: select() failed!/n");
    }else if(ret==0){
      printf("RecvThread: select() time out./n");
    }else{
      for(int i=0; i<count; i++){
         if(FD_ISSET(sock[i],&readSet)){
            int bytes=recv(sock[i],buf,sizeof(buf)-1,0);
            if(bytes==-1){
              printf("RecvThread: recv failed./n");
              clients.RemoveClient(sock[i]);
              close(sock[i]);
            }else if(bytes==0){
              printf("RecvThread: socket closed by the other side./n");
              clients.RemoveClient(sock[i]);
              close(sock[i]);
            }else{
              ProcessMessage(sock[i],buf,sizeof(buf),bytes);
            }
         }
      }
    }
    
  }
 
 return NULL;
}
void* SendThread(void*){
   fd_set writeSet;
   int sock[MAX_CLIENT];
   char buf[BUFFER_SIZE];
   struct timeval timeout;
   while(!toStop){
       int ret = messageBuffer.GetMessage(buf,sizeof(buf));
       printf("get a message from buffer./n");
       if(ret==-1){
          printf("SendThread: exit./n");
          return NULL;
       }
       int count = clients.GetAllSocket(sock,MAX_CLIENT);
       FD_ZERO(&writeSet);
       int maxfd = 0;
       for(int i=0;i<count;i++){
          FD_SET(sock[i],&writeSet);
          if(sock[i]>maxfd){
              maxfd = sock[i];
          }
       }
       timeout.tv_sec = 2;
       timeout.tv_usec = 0;
       ret = select(maxfd+1,NULL,&writeSet,NULL,&timeout);
       if(toStop){
          printf("SendThread: exit./n");
          return NULL;
       }
       if(ret==-1){
         printf("SendThread: select() failed!/n");
       }else if(ret==0){
         printf("SendThread: select() time out./n");
       }else{
         for(int i=0;i<count;i++){
            if(FD_ISSET(sock[i],&writeSet)){
                int messageLen = strlen(buf);
                int bytes = send(sock[i],buf,messageLen,0);
                if(bytes==-1){
                   printf("SendThread: send() failed./n");
                }else if(bytes!=messageLen){
                   printf("SendThread: send message trunked.");
                }else{
                   //do nothing
                }
            }
         }
       }
   }
   return NULL;
}
void ProcessMessage(int sock,char buf[],int bufsize,int bytes){
  struct sockaddr_in clientAddr;
  if(!clients.GetAddrBySocket(sock,&clientAddr)){
     printf("ProcessMessage: can not find socket address./n");
     return;
  }
  char ipString[16];
  unsigned char *ip = (unsigned char*)&clientAddr.sin_addr.s_addr;
  sprintf(ipString,"%u.%u.%u.%u",*ip,*(ip+1),*(ip+2),*(ip+3));
  unsigned short port = ntohs(clientAddr.sin_port);
  buf[bytes]='/0';
  printf("Message from %s:%d: %s/n",ipString,port,buf);
  const char* CMD_BYE="bye";
  if(strcmp(buf,CMD_BYE)==0){
    send(sock,CMD_BYE,strlen(CMD_BYE),0);
    clients.RemoveClient(sock);
    close(sock);
    printf("%s:%u disconnected./n", ipString, port);
    return;
  }else{
        char bufWithName[BUFFER_SIZE+NAME_LEN];
	char cmdname[5];
        char name[NAME_LEN];
	memcpy(cmdname, buf, 4);
	cmdname[4] = '/0';
        const char* CMD_NAME="name";
	if(strcmp(cmdname,CMD_NAME)==0){
	   char newname[NAME_LEN];
           int nameLen = strlen(buf+5);
           int copyLen;
           if(nameLen>=NAME_LEN){
              copyLen = NAME_LEN-1;
           }else{
              copyLen = nameLen;
           }
           memcpy(newname,buf+5,copyLen);
           newname[copyLen]='/0';
	   clients.GetName(sock,name,sizeof(name));
	   sprintf(bufWithName,"%s change name to %s",name,newname);
	   clients.PutName(sock,newname,strlen(newname));
	   messageBuffer.PutMessage(bufWithName);
        }else{           
           clients.GetName(sock,name,sizeof(name));
           sprintf(bufWithName,"%s: %s",name,buf);
	   messageBuffer.PutMessage(bufWithName);
        }
  }
}
