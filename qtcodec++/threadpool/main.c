#include <stdio.h>
#include "threadpool.h"
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void taskFucn(void *arg)
{
    int num = *(int *)arg;
    printf("thread %ld is working ,num=%d\n",pthread_self(),num);
    sleep(1);
}

int main()
{
    printf("Hello World!\n");



    //creat pool

    ThreadPool *pool= threadPoolCreat(3,10,100);
    printf("creat1");
    for(int i = 0 ;i<100;++i)
    {
        int *num = (int *)malloc(sizeof(int));
        *num = i+100;

        threadPoolAdd(pool,taskFucn,num);
    }
    sleep(30);

    threadPool_destroy(pool);
    return 0;
}
