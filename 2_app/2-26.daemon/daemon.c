/*************************************************
*文件名  ：daemon.c                
*创建者  ：Elvin                    
*创建时间：2015.07.07            
*程序说明：该程序创建一个子进程作为守护进程，父进程
          自动退出。守护进程在一定时间内向文件写入数据。
**************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int i;
    int fd;
    int flag = 1;
    char buff[64] = "sleep 10 seconds!\n";
    /* 1.创建子进程作为守护进程 */
    pid_t pid;
    pid = fork();
    if(0 > pid)
    {
        printf("Create process fail!\n");
        exit(1);
    }
    if(0 < pid)
        exit(0);
    /* 2.守护进程脱离控制终端 */
    setsid();
    /* 3.守护进程工作目录更改到根目录 */
    chdir("/");
    /* 4.对文件权限掩码清零 */
    umask(0);
    /* 5.关闭文件 */
    for(i = 0; i < 65535; i++)
    {
        close(i);
    }
    /* 在文件里周期性地写入数据 */
    while(1)
    {
        if(1 == flag)
        {
            if(-1 == (fd = open("/arm/150707_daemon/sleep.log", O_RDWR | O_CREAT, 0777)))
            {
                printf("Create file fail!\n");
                exit(1);
            }
            flag = 0;
        }
        write(fd, buff, strlen(buff));
        sleep(10);
    }
    close(fd);
    return 0;
}
