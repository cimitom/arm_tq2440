/*************************************************
*文件名  ：tcp_server.c                
*创建者  ：Elvin                    
*创建时间：2015.07.04            
*程序说明：该程序创建一个socket，利用TCP协议作为
          服务器端接收来自客户端传过来的字符串。
**************************************************/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#define PORTNUM 3333

int main()
{
    int sockfd;
    int acc_fd;
    int recv_sz;
    long addr_len;
    char buffer[128];
    char client_addr_a[10];
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    /* 1.创建socket */
    if(-1 == (sockfd = socket(AF_INET, SOCK_STREAM, 0)))
    {
        printf("Create socket fail!\n");
        exit(1);
    }
    /* 2.绑定地址 */
    bzero(&server_addr, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORTNUM);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(sockfd, (struct sockaddr*)(&server_addr), sizeof(struct sockaddr));
    /* 3.监听连接 */
    listen(sockfd, 5);
    while(1)
    {
        /* 4.等待连接 */
        addr_len = sizeof(struct sockaddr);
        if(-1 == (acc_fd = accept(sockfd,(struct sockaddr*)(&client_addr), (socklen_t *)(&addr_len))))
        {
            printf("Create server connect fail!\n");
            exit(1);
        }
        printf("The server has connect with %s\n", inet_ntoa(client_addr.sin_addr));
        /* 5.接收数据 */
        recv_sz = recv(acc_fd, buffer, 128, 0);
        buffer[recv_sz] = '\0';
        if(0 == strncmp(buffer, "quit", 4))
        {
            close(acc_fd);
            break;
        }
        printf("Server has received the message is : %s\n", buffer);
        /* 6.结束app连接 */
        close(acc_fd);

    }
    /* 7.结束socket连接 */
    close(sockfd);

    return 0;
}

