#include "threadpool.h"
#include <pthread.h>
const int NUMBER =2;


typedef struct Task{
    void (*function)(void *arg);
    void *arg;
}Task;
typedef struct ThreadPool{
    //task que
    Task *taskQ;
    int queueCapacity;  //capacity

    int queueSize;   //task size
    int queueFront;  //front get data
    int queueRear;   //rear  put data

    pthread_t managerID;
    pthread_t *threadIDs;

    int minNum;
    int maxNum;

    int busyNum;

    int liveNum;

    int exitNum;     //kill thread num
    pthread_mutex_t mutexPool;  //mutex the hole pool
    pthread_mutex_t mutexBusy;

    int shutdown;  //shut 1

    pthread_cond_t notFull;   //if full
    pthread_cond_t notEmpty;  //if empty


}ThreadPool;
//init threadpool
ThreadPool* threadPoolCreat(int min,int max,int queueSize)
{
    printf("creat1111111111\n");
    ThreadPool* pool = (ThreadPool*)malloc(sizeof(ThreadPool));
    do{

        if(pool==NULL)
        {
            printf("threadpool creat fault\n");
            break;
        }
        pool->threadIDs =(pthread_t *) malloc(sizeof(pthread_t)*max);
        if(pool->threadIDs==NULL)
        {
            printf("pthread_t creat fail....\n");
            break;
        }
        memset(pool->threadIDs,0,sizeof(pthread_t)*max);
        printf("memset\n");
        pool->maxNum =max;
        pool->minNum=min;
        pool->busyNum=0;
        pool->liveNum=min;
        pool->exitNum=0;

        if(pthread_cond_init(&pool->notEmpty,NULL)!=0 ||
                pthread_cond_init(&pool->notFull,NULL)!=0 ||
                pthread_mutex_init(&pool->mutexBusy,NULL)!=0||
                pthread_mutex_init(&pool->mutexPool,NULL)!=0)
        {
            printf("mutex or cond init fail..\n");
            break;
        }
        printf("mutex cond init success\n");
        pool->taskQ =(Task*) malloc(sizeof(Task) * queueSize);


        pool->queueCapacity = queueSize;
        pool->queueSize =0;
        pool->queueFront = 0;
        pool->queueRear =0;

        pool->shutdown=0;

        pthread_create(&pool->managerID,NULL,manager,pool);

        for(int i=0;i<min;++i)
        {
            pthread_create(&pool->threadIDs[i],NULL,worker,pool);
        }
        return pool;

    }while(0);
    if(pool&&pool->threadIDs) free(pool->threadIDs);
    if(pool&&pool->taskQ) free(pool->taskQ);
    if(pool) free(pool);
    printf("init fail\n");

    return NULL;
}






void *worker(void *arg)
{
    ThreadPool *pool =(ThreadPool *)(arg);
    while (1) {
        pthread_mutex_lock(&pool->mutexPool);

        while(pool->queueSize==0&&!pool->shutdown)
        {
            pthread_cond_wait(&pool->notEmpty,&pool->mutexPool);
            if(pool->exitNum>0)
            {
                pool->exitNum--;
                if(pool->liveNum>pool->minNum)
                {
                    pool->liveNum--;
                    pthread_mutex_unlock(&pool->mutexPool);
                    threadExit(pool);
                }

            }
        }
        if(pool->shutdown)
        {
            pthread_mutex_unlock(&pool->mutexPool);
            threadExit(pool);
        }
        Task task;
        task.function=pool->taskQ[pool->queueFront].function;
        task.arg=pool->taskQ[pool->queueFront].arg;

        //move head
        pool->queueFront=(pool->queueFront+1) % pool->queueCapacity;
        pool->queueSize--;
        //signal to producer notfull
        pthread_cond_signal(&pool->notFull);

        pthread_mutex_unlock(&pool->mutexPool);
        printf("thread %ld start work\n",pthread_self());
        pthread_mutex_lock(&pool->mutexBusy);
        pool->busyNum++;
        pthread_mutex_unlock(&pool->mutexBusy);
        task.function(task.arg);
        free(task.arg);
        task.arg=NULL;

        printf("thread %ld finish work\n",pthread_self());
        pthread_mutex_lock(&pool->mutexBusy);
        pool->busyNum--;
        pthread_mutex_unlock(&pool->mutexBusy);

    }
}

void *manager(void *arg)
{
    ThreadPool *pool =(ThreadPool *)arg;
    while (!pool->shutdown) {
        //every 3 second check
        sleep(3);

        //get the number of tasks in the thread pool and the number of the threads
        pthread_mutex_lock(&pool->mutexPool);
        int queueSize = pool->queueSize;
        int liveNum=pool->liveNum;
        pthread_mutex_unlock(&pool->mutexPool);


        //get the number of busy thread in the thread pool
        pthread_mutex_lock(&pool->mutexBusy);
        int busyNum = pool->busyNum;
        pthread_mutex_unlock(&pool->mutexBusy);

        //creat thread
        if((liveNum-busyNum)<queueSize&&liveNum<pool->maxNum)
        {
            pthread_mutex_lock(&pool->mutexPool);
            int counter = 0 ;
            for(int i=0;
                i<pool->maxNum&&
                counter<NUMBER&&
                pool->liveNum<pool->maxNum;
                ++i)
            {
                if(pool->threadIDs[i]==0)
                {
                    pthread_create(&pool->threadIDs[i],NULL,worker,pool);
                    counter++;
                    pool->liveNum++;
                }
            }
            pthread_mutex_unlock(&pool->mutexPool);
        }


        //destroy thread
        if(busyNum*2<liveNum && liveNum >pool->minNum)
        {
            pthread_mutex_lock(&pool->mutexPool);
            pool->exitNum = NUMBER;
            pthread_mutex_unlock(&pool->mutexPool);

            //let the thread killing itsself
            for (int i = 0 ;i<NUMBER;++i)
            {
                pthread_cond_signal(&pool->notEmpty);
            }
        }


    }


    return NULL;
}

void threadExit(ThreadPool *pool)
{
    pthread_t tid =pthread_self();
    for(int i = 0 ;i< pool->maxNum; i++)
    {
        if(tid == pool->threadIDs[i])
        {
            pool->threadIDs[i]=0;
            printf("thread exit is called %ld exiting \n",tid);
            break;

        }

    }
    pthread_exit(NULL);

}

void threadPoolAdd(ThreadPool *pool, void (*func)(void*), void *arg)
{
    printf("add thread\n");
    pthread_mutex_lock(&pool->mutexPool);
    while(pool->queueSize == pool->queueCapacity &&!pool->shutdown)
    {
        //queueTask full block producer thread
        pthread_cond_wait(&pool->notFull,&pool->mutexPool);
    }
    if(pool->shutdown)
    {
        pthread_mutex_unlock(&pool->mutexPool);
        return;
    }
    //add task in the rear of he queue
    pool->taskQ[pool->queueRear].function=func;
    pool->taskQ[pool->queueRear].arg = arg;
    pool->queueRear = (pool->queueRear+1)%pool->queueCapacity;
    pool->queueSize++;


    pthread_cond_signal(&pool->notEmpty);
    pthread_mutex_unlock(&pool->mutexPool);



//    pthread_mutex_unlock(&pool->mutexPool);

}

int threadPoolBusyNum(ThreadPool *pool)
{
    pthread_mutex_lock(&pool->mutexBusy);
    int busyNum = pool->busyNum;

    pthread_mutex_unlock(&pool->mutexBusy);
    return busyNum;
}

int threadPoolAliveNum(ThreadPool *pool)
{
    pthread_mutex_lock(&pool->mutexPool);
    int aliveNum = pool->liveNum;

    pthread_mutex_unlock(&pool->mutexPool);
    return aliveNum;
}

int threadPool_destroy(ThreadPool *pool)
{
    if(pool ==NULL)
    {
        return -1;
    }
    //close pool
    pool->shutdown =1;
    //block and recycle the manager thread
    pthread_join(pool->managerID,NULL);
    //awake the blocking comsumer thread  auto exit
    for(int i =0;i<pool->liveNum;++i)
    {
        pthread_cond_signal(&pool->notEmpty);
    }
    if(pool->taskQ)
    {
        free(pool->taskQ);
    }
    if(pool->threadIDs)
    {
        free(pool->threadIDs);
    }
    pthread_mutex_destroy(&pool->mutexBusy);
    pthread_mutex_destroy(&pool->mutexPool);
    pthread_cond_destroy(&pool->notEmpty);
    pthread_cond_destroy(&pool->notFull);
    free(pool);



    pool=NULL;


    return 0;
}
