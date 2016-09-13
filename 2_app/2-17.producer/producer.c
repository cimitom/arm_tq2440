#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

void main()
{
    int fd_product;
    int sd_product;
    key_t key_product;
    struct sembuf sembuf_product;    

    fd_product = open("./product.txt",O_RDWR | O_CREAT, 0777);
    
    key_product = ftok("/arm",1);
    sd_product = semget(key_product, 1, IPC_CREAT);
    semctl(sd_product, 0, SETVAL, 0);

    sleep(10);

    write(fd_product, "The Product Finished!", 21 );

    sembuf_product.sem_num = 0;
    sembuf_product.sem_op = 1;
    sembuf_product.sem_flg = SEM_UNDO;
    semop(sd_product, &sembuf_product, 1);

    close(fd_product);
}