#include <stdio.h>
#include <string.h>

int main(int argc, char ** argv)
{
    int i = 0;
    char *dest = "http://www.:google.com:80/";
    i = strstr(dest,"://")-dest+3;
    char chTmp = ':';
    char *stAfter = index(dest + i, chTmp);
    printf("%s\n",stAfter);
    return 0;
}
