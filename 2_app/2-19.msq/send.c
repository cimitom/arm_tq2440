/*********************************
*文件名  ：send.c                
*创建者  ：Elvin                    
*创建时间：2015.07.01            
*程序说明：该程序从键盘读入字符串，
          把字符串放进消息队列。
**********************************/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <stdlib.h>

#define MSG_SZ 1024
#define MSGKEYP "/arm/key_msq"
#define SHMKEYN "/arm/key_shm"

int *shm;

typedef struct msg_st{
    long msg_type;
    char msg_text[MSG_SZ];
}msg_ty;

int main()
{
    int msqid;
    int shmid;
    key_t msg_key;
    key_t shm_key;
    long msgty;
    char msgtx[MSG_SZ];
    msg_ty msg_p;

    /* 1.创建消息队列 */
    msg_key = ftok(MSGKEYP,1);
    shm_key = ftok(SHMKEYN,1);
    msqid = msgget(msg_key,IPC_CREAT);
    shmid = shmget(shm_key, sizeof(int), IPC_CREAT);
    if(-1 == shmid)
    {
        printf("Creat the shm fail!\n");
        exit(EXIT_FAILURE);
    }
    shm = (int *)shmat(shmid, NULL, 0);
    *shm = 0;

    /* 2.循环地从键盘中获得字符串，并把字符串发送到消息队列 */
    while(1)
    {
        printf("Please input the text type, 0 for end!\n");
        scanf("%ld", &msgty);

        if(0 == msgty)
        {
            *shm = 1;
            break;
        }
        printf("Please input the text content:\n");
        scanf("%s", msgtx);

        msg_p.msg_type = msgty;
        strcpy(msg_p.msg_text,msgtx);

        msgsnd(msqid, &msg_p, sizeof(msg_ty), 0);
    }
    
    /* 3.删除消息队列 */
    msgctl(msqid, IPC_RMID, 0);
    shmdt((const void *)shm);
    sleep(10);
    shmctl(shmid, IPC_RMID, 0);
    return 0;
}
