#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

void main()
{
	int val_sem;
    int fd_sem;
    int semnum_sem;
    key_t key_sem;
    struct sembuf buf_sem;

    fd_sem = open("./sem.txt",O_RDWR | O_APPEND | O_CREAT, 0777);
    printf("fd_sem val is %d\n",fd_sem);

    key_sem = ftok("/arm/key_sem", 1);
    printf("key_sem val is %d\n",key_sem);

    semnum_sem = semget(key_sem, 1, IPC_CREAT);
    printf("semnum_sem val is %d\n",semnum_sem);
    
	val_sem = semctl(semnum_sem, 0, GETVAL);
    printf("B val is %d\n", val_sem);

    buf_sem.sem_num = 0;
    buf_sem.sem_op = -1;
    semop(semnum_sem, &buf_sem, 1);

    write(fd_sem,"ccccc",5);

    buf_sem.sem_num = 0;
    buf_sem.sem_op = 1;
    semop(semnum_sem, &buf_sem, 1);

    close(fd_sem);
}