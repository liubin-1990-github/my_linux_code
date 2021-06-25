#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

//pthread_cond_t cond;
pthread_mutex_t mutex;
sem_t semp;
sem_t semc;

struct Node
{
    int number;
    struct Node *next;
};
struct Node *head =NULL;

void * producer(void *arg)
{
    while (1) {
        sem_wait(&semp);
//        pthread_mutex_lock(&mutex);
        struct Node *newnode = (struct Node*)malloc(sizeof(struct Node));
        newnode->number=rand()%1000;
        newnode->next=head;
        head = newnode;
        printf("producer,id:%ld,number: %d\n",pthread_self(),newnode->number);
        sem_post(&semc);
//        pthread_mutex_unlock(&mutex);
//        pthread_cond_broadcast(&cond);
        sleep(rand()%3);
    }
    return NULL;
}

void *consumer(void *arg)
{
    while (1) {
        sem_wait(&semc);
//        pthread_mutex_lock(&mutex);
//        while(head ==NULL)
//        {
//            //zuse
//            pthread_cond_wait(&cond,&mutex);
//        }
        struct Node *node =head;
        printf("consumer,id:%ld, number:%d\n",pthread_self(),head->number);
        head=head->next;
        free(node);
        sem_post(&semp);
//        pthread_mutex_unlock(&mutex);
        sleep(rand()%3);
    }
    return NULL;
}

int main()
{
    //comsumer source 0
    sem_init(&semp,0,5);

    sem_init(&semc,0,0);

    pthread_mutex_init(&mutex,NULL);
//    pthread_cond_init(&cond,NULL);

    pthread_t t1[5],t2[5];
    for(int i=0;i<5;++i)
    {
        pthread_create(&t1[i],NULL,producer,NULL);
    }
    for(int i=0;i<5;++i)
    {
        pthread_create(&t2[i],NULL,consumer,NULL);
    }


    for(int i=0;i<5;++i)
    {
        pthread_join(t1[i],NULL);
    }
    for(int i=0;i<5;++i)
    {
        pthread_join(t2[i],NULL);
    }
//    sleep(3);


    pthread_mutex_destroy(&mutex);
    sem_destroy(&semc);
    sem_destroy(&semp);
//    pthread_cond_destroy(&cond);
    return 0;
}
