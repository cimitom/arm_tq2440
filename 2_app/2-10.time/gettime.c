#include <stdio.h>
#include <time.h>
#include <sys/time.h>

int main()
{
    time_t ctime;
    struct tm *tm;
    struct timeval gettime;
    ctime = time(NULL);
    tm = localtime(&ctime);
    char *asct = asctime(tm);
    printf("ctime is %d\n",ctime);
    printf("localtime is %d,%d,%d %d : %d : %d\n",tm->tm_year,tm->tm_mon,tm->tm_mday,tm->tm_hour,tm->tm_min,tm->tm_sec);
    printf("Now is %s\n",asct);

    gettimeofday(&gettime, NULL);
    printf("sec is %d,usec is %d\n", gettime.tv_sec,gettime.tv_usec);
    return 0;
}