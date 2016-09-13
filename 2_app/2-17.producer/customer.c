#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

void main()
{
    int sd_product;
    key_t key_product;
    struct sembuf sembuf_product;    
    key_product = ftok("/arm",1);
    sd_product = semget(key_product, 1, IPC_CREAT);

    sembuf_product.sem_num = 0;
    sembuf_product.sem_op = -1;
    sembuf_product.sem_flg = SEM_UNDO;
    semop(sd_product, &sembuf_product, 1);

    system("cp ./product.txt ./ship/product.txt");

    sembuf_product.sem_num = 0;
    sembuf_product.sem_op = 1;
    sembuf_product.sem_flg = SEM_UNDO;
    semop(sd_product, &sembuf_product, 1);


}