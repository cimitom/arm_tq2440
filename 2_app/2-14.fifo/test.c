#include <stdio.h>
#include <string.h>

void main()
{
    char c_buf[512];
    int c_len;
    printf("Please input some words:\n");
    scanf("%[^\n]", c_buf);

    c_len = strlen(c_buf);
    printf("len is %d\n",c_len);
    printf("The words :\n");
    printf("%s\n",c_buf);
}