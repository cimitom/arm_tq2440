/*************************************************
*文件名  ：udp_client.c                
*创建者  ：Elvin                    
*创建时间：2015.07.04            
*程序说明：该程序创建一个socket，利用UDP协议
           作为客户端向服务器端传送字符串。
**************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFF_SZ 128

int main(int argc, char **argv)
{
    int sockfd;
    int send_sz;
    char buff[BUFF_SZ];
    struct sockaddr_in server_addr;
    if(3 != argc)
    {
        printf("Usage: %s serverIP serverPort\n",argv[0]);
        exit(1);
    }
    /* 1.创建套接字 */
    if(-1 == (sockfd = socket(AF_INET, SOCK_DGRAM, 0)))
    {
        printf("Create socket fail!\n");
        exit(1);
    }
    /* 2.发送数据 */
    bzero(&server_addr, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    while(1)
    {
        bzero(buff,sizeof(buff));
        printf("Please input something send to server:\n");
        fgets(buff, sizeof(buff), stdin);
        send_sz = sendto(sockfd, buff, sizeof(buff), 0, (struct sockaddr *)(&server_addr), sizeof(struct sockaddr));
        if(-1 != send_sz)
        {
            printf("The message had be sended\n");
        }
        if(0 == strncmp(buff, "quit", 3))
        {
            printf("The client close! Good bye!\n");
            break;
        }
    }

    /* 3.结束连接 */
    close(sockfd);

    return 0;
}
