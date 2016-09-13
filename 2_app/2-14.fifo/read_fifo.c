#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd_fifo;
//    int s_len;
    char output_buf[512];

//    s_len = strlen(input);
    
    fd_fifo = open("/home/elvin/myfifo",O_RDONLY);
    read(fd_fifo, output_buf, 512);
    printf("The fifo words:\n");
    printf("%s\n",output_buf);
    close(fd_fifo);
    unlink("/home/elvin/myfifo");
    return 0;
}
