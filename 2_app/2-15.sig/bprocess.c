#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void myfunc()
{
    printf("Process B was receive the signal !\n");
}

void main()
{
    signal(SIGINT,myfunc);
    pause();
}