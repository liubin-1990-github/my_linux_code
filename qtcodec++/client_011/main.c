#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>

int main()
{
    setbuf(stdout,NULL);
    //1 creat socket
    int fd= socket(AF_INET,SOCK_STREAM,0);
    if(fd==-1)
    {
        perror("socket");
    }

    //2 connect server
    struct sockaddr_in saddr;
    saddr.sin_family =AF_INET;
    saddr.sin_port =htons(9999);
    inet_pton(AF_INET,"127.0.0.1",&saddr.sin_addr.s_addr);  //local ip save in saddr.sin_addr.s_addr
    int ret=connect(fd,(struct sockaddr*)&saddr,sizeof(saddr) );


    if(ret==-1)
    {
        perror("connect");
        return -1;
    }


    int number = 0 ;

    //communicate
    while (1) {
        //send
        char buff[1024];
         memset(buff,0,sizeof(buff));
        sprintf(buff,"hello world, %d...\n",number++);
        send(fd,buff,strlen(buff)+1,0);
        memset(buff,0,sizeof(buff));

        //recv


        int len = recv(fd,buff,sizeof(buff),0);
        if(len>0)
        {
            printf("client say :%s\n",buff);
//            send(fd,buff,len,0);

        }
        else if(len ==0)
        {
            printf("server disconnceted");
            break;
        }
        else
        {
            perror("error");
            break;
        }
        sleep(1);
    }
    close(fd);



}
