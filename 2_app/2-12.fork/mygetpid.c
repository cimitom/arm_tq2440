#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void main()
{
    pid_t pid_01;
    pid_01 = getpid();
    printf("pid is %d\n",pid_01);
}