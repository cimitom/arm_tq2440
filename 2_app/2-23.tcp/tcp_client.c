/*************************************************
*文件名  ：tcp_server.c                
*创建者  ：Elvin                    
*创建时间：2015.07.04            
*程序说明：该程序创建一个socket，利用TCP协议
           作为客户端向服务器端传送字符串。
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
    char server_addr_a[4];
    long addr_len;
    char buffer[128];
    struct sockaddr_in server_addr;

    /* 1.创建socket */
    if(-1 == (sockfd = socket(AF_INET, SOCK_STREAM, 0)))
    {
        printf("Create socket fail!\n");
        exit(1);
    }
    /* 2.建立连接 */
    bzero(&server_addr, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORTNUM);
    server_addr.sin_addr.s_addr = inet_addr("192.168.123.4");
    if(-1 == (connect(sockfd, (struct sockaddr*)(&server_addr), sizeof(struct sockaddr))))
    {
        printf("Create connect fail!\n");
        exit(1);
    }


    /* 3.发送数据 */
    printf("Please input something :\n");
    fgets(buffer, 128, stdin);
    send(sockfd, buffer, strlen(buffer), 0);
    
//        if(0 == strcmp(buffer, "quit"))
//            break;
    
    /* 4.结束app连接 */
    close(sockfd);

    return 0;
}

