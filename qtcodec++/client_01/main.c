#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main()
{
    int cfd;
    int conter = 10;
    char buf[BUFSIZ];
    struct sockaddr_in serv_addr; //sevr
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9527);

    inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr.s_addr);
    cfd=socket(AF_INET,SOCK_STREAM,0);

    int ret= connect(cfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));




    while (--conter) {
        write(cfd,"hello",5);
         ret =read(cfd,buf,sizeof(buf));
        write(STDOUT_FILENO,buf,ret);
        sleep(1);
    }
    close(cfd);

    return 0;
}
