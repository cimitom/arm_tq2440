/*************************************************
*文件名  ：sync_1.c                
*创建者  ：Elvin                    
*创建时间：2015.07.03            
*程序说明：该程序模拟两同学（线程），A同学先扫五次地
           然后B同学才能进行拖地的程序（B同学采用轮
           询方式询问A同学是否已扫完地）。
**************************************************/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_t stu_thread[2];
pthread_mutex_t mutex_lock;
int number = 0;

/* A同学线程函数 */
void * studentA()
{
    int i = 0;
    /* 扫五次地 */
    for(i = 0; i < 5; i++)
    {
        pthread_mutex_lock(&mutex_lock);
        number++;
        printf("studentA has finished the work one time\n");
        pthread_mutex_unlock(&mutex_lock);
        sleep(1);
    }
    if(5 <= number)
    {
        printf("studentA has finished all works!!!\n");
    }

    /* 退出线程 */
    pthread_exit(NULL);
}

/* B同学要拖地的线程函数 */
void * studentB()
{
    /* 轮询地不断检查A同学是否已经扫完地 */
    while(1)
    {
        pthread_mutex_lock(&mutex_lock);
        if(5 <= number)
        {
            /* 若A扫完地，进行拖地 */
            number = 0;
            printf("studentB has finished his work!!!\n");
            pthread_mutex_unlock(&mutex_lock);
            break;
        }
        else
        {
            pthread_mutex_unlock(&mutex_lock);
            sleep(2);
        }
    }
    /* 退出线程 */
    pthread_exit(NULL);
}

int main()
{
    /* 初始化互斥锁 */
    pthread_mutex_init(&mutex_lock, NULL);

    /* 创建studentA的进程 */
    pthread_create(&stu_thread[0], NULL, studentA, NULL);

    /* 创建studentB的进程 */
    pthread_create(&stu_thread[1], NULL, studentB, NULL);
    
    /* 等待studentA进程的结束 */
    pthread_join(stu_thread[0], NULL);

    /* 等待studengB进程的结束 */
    pthread_join(stu_thread[1], NULL);

    return 0;
}
