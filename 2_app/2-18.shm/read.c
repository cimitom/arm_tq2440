/*********************************
*文件名  ：read.c                
*创建者  ：Elvin                    
*创建时间：2015.06.30            
*程序说明：该程序从共享内存仲读取一字符串，
          把字符串打印出来。
**********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

#define TEXT_SZ 2048
#define SHMKEYN "/arm/key_shm"

struct shm_user_st
{
    int flag;
    char some_text[TEXT_SZ];
};

int main()
{
    int shmid;
    int running = 1;
    key_t shm_key;
    char buf[TEXT_SZ];
    struct shm_user_st *shm_user_p;

    //1.创建/获取共享内存
    shm_key = ftok(SHMKEYN, 1);
    shmid = shmget(shm_key, sizeof(struct shm_user_st), IPC_CREAT);
    if(-1 == shmid)
    {
        printf("Creat the shm fail!\n");
        exit(EXIT_FAILURE);
    }
    
    //2.映射共享内存
    shm_user_p = (struct shm_user_st *)shmat(shmid, NULL, 0);
    shm_user_p->flag = 0;

    //3.循环，从键盘获取字符串并填进共享内存
    while(running)
    {
        if(1 == shm_user_p->flag)
        {
            printf("write process written: %s", shm_user_p->some_text);
            shm_user_p->flag = 0;
        }
        if(0 == strncmp(shm_user_p->some_text, "end", 3))
        {
            running = 0;
        }
    }
    //4.脱离共享内存
    shmdt((const void *)shm_user_p);

    //5.删除共享内存
    shmctl(shmid, IPC_RMID, 0);
    
    return 0;
}
