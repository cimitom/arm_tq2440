#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main()
{
    pid_t pid_01;
    pid_01 = vfork();
    if( pid_01 > 0)
    {
        printf("father \n");
        exit(0);
    }
    else
    {
        printf("child \n");
        exit(0);
    }
}