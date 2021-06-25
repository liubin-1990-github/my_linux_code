#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct ThreadPool ThreadPool;
//init threadpool
ThreadPool* threadPoolCreat(int min,int max,int queueSize);
//destroy threadpool
int threadPool_destroy(ThreadPool *pool);
//add task in pool
void threadPoolAdd(ThreadPool *pool,void (*func)(void*),void *arg);
//get the number that are workingg
int threadPoolBusyNum(ThreadPool *pool);
//get the number that living
int threadPoolAliveNum(ThreadPool *pool);
/////
void *worker(void *arg);
void *manager(void *arg);
void threadExit(ThreadPool *pool);


#endif // THREADPOOL_H
