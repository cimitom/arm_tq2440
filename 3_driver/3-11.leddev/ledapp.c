
/*************************************************
*文件名  ：ledapp.c                
*创建者  ：FD                    
*创建时间：2015.08.19            
*程序说明：该程序为一个应用程序，通过LED_ON和LED_OFF
           来操控开发板上的LED的亮灭状态
**************************************************/
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "leddev.h"

int main(int argc, char **argv)
{
    int cmd = 0;
    if(!(strcmp(argv[1],"ON")))
        cmd = 1;
    else
        if(!(strcmp(argv[1],"OFF")))
            cmd = 0;
        else
        {
            printf("cmd error!\n");
            return -EINVAL;
        }
    int fd;
    fd = open("/dev/leddev0", O_RDWR);
    switch (cmd)
    {
        case 1:
            ioctl(fd,LED_ON);
            break;
        case 0:
            ioctl(fd,LED_OFF);
            break;
        default:
            printf("cmd error!\n");
            break;
    }
    close(fd);
    return 0;
}