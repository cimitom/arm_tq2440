#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main()
{
    int fd_fifo;
    int s_len;
    char input_buf[20];
    
    printf("Please input some words:\n");

    //用scanf获取带空格的字符串，用正则表达式
    scanf("%[^\n]",input_buf);
    s_len = strlen(input_buf);
    
    mkfifo("/home/elvin/myfifo",0777);
    fd_fifo = open("/home/elvin/myfifo",O_WRONLY);
    write(fd_fifo, input_buf, s_len);
    close(fd_fifo);
    return 0;
}
