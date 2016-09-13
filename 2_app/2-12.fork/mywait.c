#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void main()
{
    pid_t pid_01, pid_02;
    pid_01 = fork();
    if( pid_01 > 0)
    {
        wait(NULL);
        printf("father\n");
    }
    else
    {
        execl("/bin/ls","ls","/arm/",NULL);
    }
}
