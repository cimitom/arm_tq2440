#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main()
{
    execl("/bin/ls","ls","/arm/",NULL);
    printf("Hello\n");
}