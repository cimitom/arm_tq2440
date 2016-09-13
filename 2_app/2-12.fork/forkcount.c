#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main()
{
    pid_t pid_01;
    int count = 0;
    pid_01 = vfork();
    count++;
 
    printf("%d\n",count);
    exit(0);
}