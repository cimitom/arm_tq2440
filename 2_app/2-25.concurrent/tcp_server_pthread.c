/******************************************
*文件名  ：tcp_server_pthread.c                
*创建者  ：Elvin                    
*创建时间：2015.07.05            
*程序说明：该程序创建一个socket，利用TCP协议
          作为服务器端,采用多进程并发方式接收
          来自多个客户端传过来的字符串。
*******************************************/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>

#define PORTNUM 3333
#define BUFF_SZ 128

struct arg
{
    int con_fd;
    struct sockaddr_in con_addr;
};

void * thread_fun(void *arg)
{
    struct arg arg_thread;
    arg_thread.con_fd = ((struct arg *)arg)->con_fd;
    arg_thread.con_addr = ((struct arg *)arg)->con_addr;

    /* 5.接收数据 */
    char buff[BUFF_SZ];
    bzero(buff, sizeof(buff));
    int recv_sz = 0;
    while(1)
    {
         recv_sz = recv(arg_thread.con_fd, buff, BUFF_SZ, 0);
        if(0 != recv_sz)
        {
            buff[recv_sz] = '\0';
            printf("Server has received the message from : %s\n", inet_ntoa(arg_thread.con_addr.sin_addr.s_addr));
            printf("The message is : %s\n", buff);        
            recv_sz = 0;
            if(0 == strncmp(buff, "quit", 4))
            {
                printf("Client with %s will be close!\n", inet_ntoa(arg_thread.con_addr.sin_addr.s_addr));
                /* 6.结束app连接 */
                close(arg_thread.con_fd);
                pthread_exit(NULL);
            }
            if(0 == strncmp(buff, "end", 3))
            {
                printf("Server and Client will be close!\n");
                /* 6.结束app连接 */
                close(arg_thread.con_fd);
                exit(0);   
            }
        }
    }
       
}


int main()
{
    int sockfd;
    int acc_fd;
    pthread_t thread_id;
    long addr_len;
//    char client_addr_a[10];
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
        printf("The server has connect with %s\n", inet_ntoa(client_addr.sin_addr.s_addr));

        struct arg arg_thread;
        arg_thread.con_fd = acc_fd;
        memcpy(&(arg_thread.con_addr), &client_addr, sizeof(struct sockaddr_in));
        if(-1 == pthread_create(&thread_id, NULL, thread_fun, (void *)&arg_thread))
        {
            printf("Create pthread fail!\n");
            exit(1);
        }

    }
}

