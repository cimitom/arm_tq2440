#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "memdev.h"

int main()
{
    int fd;
    fd = open("/dev/memdev0",O_RDWR);
    ioctl(fd, MEM_SET, 115200);
    ioctl(fd, MEM_RESTART);
    close(fd);
    return 0;
}