
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define SERV_PORT 9527

int main(int argc,char *argv)
{
    int lfd=0;
    int cfd=0;
    int ret , i;
    char buf[BUFSIZ],clit_IP[1024];
    struct sockaddr_in serv_addr,clit_addr;
    socklen_t clit_addr_len;

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr =htonl(INADDR_ANY);


    lfd= socket(AF_INET,SOCK_STREAM,0);

    bind(lfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));

    listen(lfd,128);

    clit_addr_len = sizeof(clit_addr);
    cfd = accept(lfd,(struct sockaddr *)&clit_addr,&clit_addr_len);
    printf("client ip:%s port:%d\n",inet_ntop(AF_INET,&clit_addr.sin_addr.s_addr,clit_IP,sizeof(clit_IP)),
           ntohs(clit_addr.sin_port)
           );


    while (1) {
        ret =read(cfd,buf,sizeof(buf));
        write(STDOUT_FILENO,buf,ret);

        for(i=0;i<ret;i++)
        {
            buf[i]=toupper(buf[i]);
        }

        write(cfd,buf,ret);
    }

    close(lfd);
    close(cfd);

    return 0;
}
