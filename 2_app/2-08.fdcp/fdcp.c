/*********************************
*文件名  ：fdcp.c                
*创建者  ：Elvin                    
*创建时间：2015.04.21            
*程序说明：该程序用来复制一个文件 
*********************************/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int fd_s, fd_t, flag;
    char buf[512];
/****************************************
*函数名  ：open
*函数功能：打开或创建一个文件
*参数    ：pathname, flags. mode    
*返回值  ：成功：返回文件描述符， 失败：-1
*****************************************/
    fd_s = open(argv[1], O_RDONLY);
    fd_t = open(argv[2], O_RDWR | O_CREAT, 0777);

    while((flag = read(fd_s, buf, 512)) >0 )
        write(fd_t, buf, flag);

    close(fd_s);
    close(fd_t);

    return 0;
}
