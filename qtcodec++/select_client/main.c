#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd == -1)
    {
        perror("socket");
        exit(0);
    }

    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port = htons(9999);
    inet_pton(AF_INET,"127.0.0.1",&addr.sin_addr.s_addr);
    int ret = connect(fd,(struct sockaddr*)&addr,sizeof(addr));
    if(ret==-1)
    {
        perror("connect");
        exit(1);
    }
    while (1)
    {
        char buf[1024];
        fgets(buf,sizeof(buf),stdin);
        write(fd,buf,sizeof(buf));
        read(fd,buf,sizeof(buf));
        printf("recv buf: %s\n",buf);
        sleep(1);
    }
    close(fd);


    return 0;
}
