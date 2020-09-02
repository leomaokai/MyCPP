//code12.cpp code_tree
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <assert.h>
#include <sys/epoll.h>
#define MAX_USER 2
#define BUFFER_SIZE 64

struct epoll_event events[MAX_USER];
int epfd = epoll_create(10);
int main()
{
    //第一步:创建服务端的socket
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(socket >= 0);

    //第二步:绑定地址与端口号
    int ret = 0;
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(54321);
    ret = bind(sockfd, (struct sockaddr *)&address, sizeof(address));
    assert(ret != -1);

    //第三步:把socket设置为监听模式
    ret = listen(sockfd, 5);
    assert(ret != -1);

    //第四步:接受客户端连接
    for (int i = 0; i < MAX_USER; ++i)
    {
        struct epoll_event ev;
        struct sockaddr_in client;
        socklen_t clientlen = sizeof(client);
        ev.data.fd = accept(sockfd, (struct sockaddr *)&client, &clientlen);
        printf("connected with ip %s\n", inet_ntoa(client.sin_addr));
        ev.events = EPOLLIN;
        epoll_ctl(epfd, EPOLL_CTL_ADD, ev.data.fd, &ev);
    }

    //第五步:与客户端通信
    char buffer[BUFFER_SIZE];
    while (1)
    {
        ret = epoll_wait(epfd, events, 2, -1);
        for (int i = 0; i < ret; ++i)
        {
            memset(buffer, 0, BUFFER_SIZE);
            int recvret = recv(events[i].data.fd, buffer, BUFFER_SIZE, 0);
            if (recvret > 0)
                printf("recv the data from the user \n");
            else
                continue;
        }
    }
}
