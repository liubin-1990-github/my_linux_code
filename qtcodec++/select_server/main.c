#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
    int lfd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(9999);
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    int ret = bind(lfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
    ret=listen(lfd,64);

    //readset init
    fd_set redset;
    FD_ZERO(&redset);
    FD_SET(lfd,&redset);
    fd_set temp;
    int maxfd=lfd;

    while(1)
    {
        temp=redset;
        int ret = select(maxfd+1,&temp,NULL,NULL,NULL);
        if(FD_ISSET(lfd,&temp))
        {
            //connnect
            int cfd = accept(lfd,NULL,NULL);//second parameter client addr data
            FD_SET(cfd,&redset);
            maxfd =cfd>maxfd?cfd:maxfd;
        }
        //no new connect  use for conmmunicate
        for(int i=0;i<=maxfd;++i)
        {
            if(i!=lfd&&FD_ISSET(i,&temp))
            {
                char buf[1024]={0};
                int len =recv(i,buf,sizeof(buf),0);
                if(len == -1)
                {
                    perror("recv error");
                    exit(1);
                }
                else if(len ==0)
                {
                    printf("client disconnected");
                    FD_CLR(i,&redset);
                    close(i);
                    break;
                }
                printf("read buf =%s\n",buf);
                for(int i = 0;i<len;++i)
                {
                    buf[i]=toupper(buf[i]);
                }
                printf("after buf =%s\n",buf);
                ret=send(i,buf,strlen(buf)+1,0);
                if(ret==-1)
                {
                    perror("send error");
                    exit(1);
                }
            }
        }

    }


//    printf("client ip: %s,port : %d\n",inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,
//                                                 ipbuf,sizeof(ipbuf)),
//           client_addr.sin_port);



    close(lfd);
    return 0;




}
