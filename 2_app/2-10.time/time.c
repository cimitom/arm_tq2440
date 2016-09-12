#include <stdio.h>
#include <time.h>

int main()
{
    time_t ctime;
    ctime = time(NULL);
    printf("ctime is %d\n",ctime);
    return 0;
}