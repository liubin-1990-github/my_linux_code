#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

void *work(void *arg);
struct SockInfo
{
    struct sockaddr_in addr;
    int fd;
};
struct SockInfo infos[512];

int main()
{
    setbuf(stdout,NULL);
    //1 creat socket
    printf("hello world");
    int fd= socket(AF_INET,SOCK_STREAM,0);
    if(fd==-1)
    {
        perror("socket");

    }
    printf("creat socket success");

    //2 bind local ip port
    struct sockaddr_in saddr;
    saddr.sin_family =AF_INET;
    saddr.sin_port =htons(9999);
    saddr.sin_addr.s_addr=INADDR_ANY;
    int ret=bind(fd,(struct sockaddr * )&saddr,sizeof(saddr));
    if(ret==-1)
    {
        perror("listen");
        return -1;
    }



    ret = listen(fd,128);


    //block waiting connect
    printf("waiting  connect");
    struct sockaddr_in caddr;
    int addrlen = sizeof(caddr);
    while(1)
    {
        int cfd = accept(fd,(struct sockaddr*)&caddr,&addrlen);
        if(cfd==-1)
        {
            perror("accept");
            break;
        }
        pthread_t tid;
        pthread_create(&tid,NULL,work,NULL);
        pthread_detach(tid);
    }
    close(fd);

}


void *work(void *arg)
{
    //connect suceess print client ip and port
    char ip[32] = {0};
    printf("client ip:%s,port:%d\n",
           inet_ntop(AF_INET,&caddr.sin_addr.s_addr,ip,sizeof(ip)),
           ntohs(caddr.sin_port));  //net port to local swicth
                                        //net ip to local

    char buff[1024];
    //communicate
    while (1) {
        //recieve
        ;
        memset(buff,0,sizeof(buff));
        int len = recv(cfd,buff,sizeof(buff),0);
        if(len>0)
        {
            printf("client say :%s\n",buff);
            send(cfd,buff,len,0);

        }
        else if(len ==0)
        {
            printf("client disconnceted");
            break;
        }
        else
        {
            perror("error");
            break;
        }
    }
    close(cfd);
    close(fd);



}
