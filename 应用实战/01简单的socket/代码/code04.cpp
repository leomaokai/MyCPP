#include"myhead.h"
int main()
{
	
	const char* ip="192.168.64.128";
    
    Client client;
    if(client.CliToSer(ip,54321)==false)
        return -1;
    
    char buffer[1024];
    int ret=0;
    for(int i=0;i<3;++i)
    {
        memset(buffer,0,BUFFER_SIZE);
	strcpy(buffer,"数据");
	ret=client.Send(buffer,strlen(buffer));
	if(ret<=0)
		break;
	printf("ret=%d,发送%d次%s\n",ret,i+1,buffer);
	memset(buffer,0,BUFFER_SIZE);
	ret=client.Recv(buffer,sizeof(buffer));
	if(ret<=0)
		break;
	printf("ret=%d,接收:%s\n",ret,buffer);
	sleep(2); 
    }
}  
