/*************************************************
*文件名  ：udp_server.c                
*创建者  ：Elvin                    
*创建时间：2015.07.05            
*程序说明：该程序创建一个socket，利用UDP协议作为
          服务器端接收来自客户端传过来的字符串。
**************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORTNUM 3333
#define BUFF_SZ 128

int main()
{
    int sockfd;
    int recv_sz;
    int cliaddr_sz;
    char buff[BUFF_SZ];
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    
    /* 1.创建UDP套接字 */
    if(-1 == (sockfd = socket(AF_INET, SOCK_DGRAM, 0)))
    {
        printf("Create socket fail!\n");
        exit(1);
    }
    /* 2.绑定地址 */
    bzero(&server_addr, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORTNUM);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(sockfd, (struct sockaddr *)(&server_addr), sizeof(struct sockaddr));
    while(1)
    {
        bzero(buff,sizeof(buff));
        /* 3.接收数据 */
        cliaddr_sz = sizeof(struct sockaddr);
        recv_sz = recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr *)(&client_addr), &cliaddr_sz);
        buff[recv_sz] = '\0';
        printf("The server has received message from : %s\n", inet_ntoa(client_addr.sin_addr.s_addr));
        printf("The message is : %s\n", buff);
        if(0 == strncmp(buff, "quit", 3))
        {
            printf("The server close! Good bye!\n");
            break;
        }
    }

    /* 4.结束连接 */
    close(sockfd);
    
    return 0;
}
