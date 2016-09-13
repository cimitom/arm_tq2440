#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void main()
{
    int i;
    char input_buf[512];
    for(i = 0; i < 512; i++)
        input_buf[i] = '\0';
    char output_buf[512];
    int pipe_fd[2];
    int file_fd;
    int count;
    pid_t pid = 0;

    printf("Please input some words:\n");
    scanf("%s",input_buf);
    count = strlen(input_buf);
    pipe(pipe_fd);

    pid = fork();

    if(pid > 0)
    {
        write(pipe_fd[1], input_buf, count);
        wait(NULL);
        close(pipe_fd[1]);
        exit(0);
    }
    else
    {
        file_fd = open("./file.txt", O_RDWR | O_CREAT, 0777);
        count = read(pipe_fd[0], output_buf, count);
        write(file_fd, output_buf, count);
        close(pipe_fd[0]);
        close(file_fd);
        exit(0);
    }
}