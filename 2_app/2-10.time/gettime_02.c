#include <stdio.h>
#include <time.h>
#include <sys/time.h>

int main()
{
    struct timeval *gt;
    gettimeofday(gt, NULL);
    printf("sec is %d,usec is %d\n", gt->tv_sec,gt->tv_usec);
    return 0;
}