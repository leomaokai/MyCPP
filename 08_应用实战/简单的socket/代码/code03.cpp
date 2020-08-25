#include"myhead.h"


int main()
{
    Server server;
    
    if(server.InitServer(54321)==false)
        return -1;
    if(server.Accept()==false)
        return -1;
    printf("connect ok\n");
    
    char buffer[BUFFER_SIZE];
    while(1)
    {
        memset(buffer,0,BUFFER_SIZE);
        if(server.Recv(buffer,BUFFER_SIZE-1)<=0)
            break;
        printf("接收: %s\n",buffer);
        
        strcpy(buffer,"成功接收");
        if(server.Send(buffer,strlen(buffer))<=0)
            break;
        printf("发送: %s\n",buffer);
    }
    printf("连接断开\n");
}
