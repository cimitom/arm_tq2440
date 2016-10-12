
/*************************************************
*�ļ���  ��ledapp.c                
*������  ��FD                    
*����ʱ�䣺2015.08.19            
*����˵�����ó���Ϊһ��Ӧ�ó���ͨ��LED_ON��LED_OFF
           ���ٿؿ������ϵ�LED������״̬
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