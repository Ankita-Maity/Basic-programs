#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <fcntl.h>

#define SIZE 1024

int main()
{

    char buf[SIZE];
    int file_read_len,fd;
    int serversock,clientsock;
    struct sockaddr_in clientadd;
    struct sockaddr_in serveradd;
    

    (serversock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0? printf("Error Creating Socket Instance\n") : printf("SOcket Created Successfully\n");

    memset(&serveradd,0,sizeof(serveradd));

    serveradd.sin_family=AF_INET;
    serveradd.sin_port=htons(8040);
    serveradd.sin_addr.s_addr=htonl(INADDR_ANY);

    (bind(serversock,(struct sockaddr *)&serveradd,sizeof(serveradd)))<0? printf("Error Binding\n") : printf("Successful Binding\n");

    (listen(serversock,1))<0? printf("Error Listening\n") : printf("Listening\n");

    unsigned int clientsize=sizeof(clientadd);
    (clientsock=accept(serversock,(struct sockaddr *)&clientadd,&clientsize))<0? printf("Error Accepting\n"):printf("Accepting Successful\n");


    (fd = open("SentFile", O_WRONLY | O_CREAT, 0700))<0 ? printf("Error Opening\n") : printf("File opened & Written\n");
    memset(buf, 0, SIZE);
    file_read_len = read(clientsock, buf, SIZE);
    write(fd, buf, file_read_len);
    close(clientsock);
    close(fd);
    close(serversock);



}
