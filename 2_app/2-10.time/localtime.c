#include <stdio.h>
#include <time.h>

int main()
{
    time_t ctime;
    struct tm *tm;
    ctime = time(NULL);
    tm = localtime(&ctime);
    printf("ctime is %d\n",ctime);
    printf("localtime is %d,%d,%d %d : %d : %d\n",tm->tm_year,tm->tm_mon,tm->tm_mday,tm->tm_hour,tm->tm_min,tm->tm_sec);
    return 0;
}