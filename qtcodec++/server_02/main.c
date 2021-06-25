#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <threadpool/threadpool.h>

void acceptConnect(void *arg);

struct SockInfo
{
    int fd;   //communicate
    pthread_t tid;   //thread id
    struct sockaddr_in addr;  //addr info

};

typedef struct PoolInfo
{
    ThreadPool* p;
    int fd;
}PoolInfo;


void working(void *arg)
{

    struct SockInfo* info = (struct SockInfo*)arg;
    char ip[32] = {0};
    printf("client ip:%s,port:%d\n",
           inet_ntop(AF_INET,&info->addr.sin_addr.s_addr,ip,sizeof(ip)),
           ntohs(info->addr.sin_port));  //net port to local swicth
                                        //net ip to local
    while(1)
    {
        //recv
        char buf[1024]={0};
        int ret = read(info->fd,buf,sizeof(buf));
        if(ret == 0)
        {
            printf("client disconnect");
            info->fd = -1;
            break;
        }
        else if(ret == -1)
        {
            printf("failed");
            info->fd=-1;
            break;
        }
        else
        {
            printf("client fd %d:  say :%s\n",info->fd,buf);
            write(info->fd,buf,strlen(buf)+1);
        }

    }
    close(info->fd);

}

int main()
{
    //creat fd communicate
    int fd = socket(AF_INET,SOCK_STREAM,0);
    //bind address
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port = htons(9999);  //host to n
    addr.sin_addr.s_addr=INADDR_ANY;
    int ret = bind(fd,(struct sockaddr*)&addr,sizeof(addr));
    if(ret == -1)
    {
        perror("bind");
        return 0 ;
    }
    //listen
    ret=listen(fd,200);
    //waiting for connected


    //init data

    //creatThreadPool
    ThreadPool *pool = threadPoolCreat(4,10,100);
    PoolInfo *info = (PoolInfo *)malloc(sizeof(PoolInfo));
    info->fd =fd;
    info->p=pool;
    threadPoolAdd(pool,acceptConnect,info);
    pthread_exit(NULL);

    return 0;
}

void acceptConnect(void *arg)
{
    PoolInfo *poolInfo=(PoolInfo *)arg;

    while (1)
    {
        socklen_t len = sizeof(struct sockaddr);
        //creat thread
        struct SockInfo *pinfo;
        pinfo=(struct SockInfo*)malloc(sizeof(struct SockInfo));
        //struct pinfo communicate
        pinfo->fd= accept(poolInfo->fd,(struct sockaddr*)&pinfo->addr,&len);
        printf("thread,connfd: %d\n",pinfo->fd);

//        pthread_create(&pinfo->tid,NULL,working,pinfo);
//        pthread_detach(pinfo->tid);
        threadPoolAdd(poolInfo->p,working,pinfo);
    }

    close(poolInfo->fd);
}
