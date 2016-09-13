#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>

void main(int argc, char **argv)
{
    pid_t pid_sig;
    pid_sig = atoi(argv[1]);
    kill(pid_sig, SIGINT);
}