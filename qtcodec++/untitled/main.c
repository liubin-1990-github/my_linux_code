#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

struct Test
{
    int num;
    int age;
};
    struct Test t;
void * callback(void* arg)
{
    for(int i =0;i<5;++i)
    {
        printf("zixiancheng: i=%d\n",i);
    }
    printf("zixiancheng:%ld\n",pthread_self());

    t.age=100;
    t.num =7;
    pthread_exit(&t);

}
int main()
{
    pthread_t tid;
    printf("hello world");
    pthread_create(&tid,NULL,callback,NULL);

    printf("zhu xian cheng :%d \n",pthread_self());

    pthread_detach(tid);
    pthread_exit(NULL);
    return 0;
}
