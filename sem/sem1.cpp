/*================================================================
*   Copyright (C) 2022 baichao All rights reserved.
*
*   文件名称：sem1.cpp
*   创 建 者：baichao
*   创建日期：2022年06月08日
*   描    述：
*
================================================================*/

// sem1.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

//定义信号量变量

sem_t sem;

void *func1(void *arg)
{

    int i = 0;

    //申请资源 将可用资源减1
    sem_wait(&sem);

    for (i = 'A'; i <= 'Z'; i++)
    {
        putchar(i);
        fflush(stdout);
        usleep(10000); // 100ms
    }

    //释放资源 将可用资源加1
    sem_post(&sem);

    return NULL;
}

void *func2(void *arg)
{

    int i = 0;

    //申请资源 将可用资源减1
    sem_wait(&sem);

    for (i = 'a'; i <= 'z'; i++)
    {
        putchar(i);
        fflush(stdout);
        usleep(10000); // 100ms
    }

    //释放资源 将可用资源加1
    sem_post(&sem);

    return NULL;
}

int main()
{

    pthread_t tid1, tid2;

    //初始化信号量
    sem_init(&sem, 0, 1);

    //创建线程
    pthread_create(&tid1, NULL, func1, NULL);
    pthread_create(&tid2, NULL, func2, NULL);

    //等待线程结束
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("\nmain exit...\n");

    //销毁信号量
    sem_destroy(&sem);

    return 0;
}
