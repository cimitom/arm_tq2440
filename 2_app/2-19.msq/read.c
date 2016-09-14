/*************************************
*文件名  ：read.c                
*创建者  ：Elvin                    
*创建时间：2015.07.01            
*程序说明：该程序从消息队列中读入字符串，
          把字符串打印到屏幕上。
**************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>

#define MSG_SZ 1024
#define MSGKEYP "/arm/key_msq"
#define SHMKEYN "/arm/key_shm"

int msqid;
int shmid;
int *shm;

typedef struct msg_st{
    long msg_type;
    char msg_text[MSG_SZ];
}msg_ty;

void child_process()
{
    msg_ty msg_p;
    while(1)
    {     
        if(1 == *shm)
            exit(0);
        msgrcv(msqid, &msg_p, sizeof(msg_ty), 0, 0);

        printf("The message is: %s\n", msg_p.msg_text);
    }
}

int main()
{

    int i;
    int cpid;
    key_t msg_key;
    key_t shm_key;
    long msgty;
    char msgtx[MSG_SZ];


    /* 1.创建消息队列 */
    msg_key = ftok(MSGKEYP,1);
    shm_key = ftok(SHMKEYN,1);
    msqid = msgget(msg_key,IPC_EXCL);
    shmid = shmget(shm_key, sizeof(int), IPC_CREAT);
    if(-1 == shmid)
    {
        printf("Creat the shm fail!\n");
        exit(EXIT_FAILURE);
    }
    shm = (int *)shmat(shmid, NULL, 0);

    /* 2.创建三个进程，循环地从消息队列取出消息并打印 */
    for(i = 0; i < 3; i++)
    {
        cpid = fork();
        if(cpid < 0)
        {
            printf("Creat child process fail!\n");
        }
        else if(0 == cpid)
            child_process();
    }
    
    return 0;
}
