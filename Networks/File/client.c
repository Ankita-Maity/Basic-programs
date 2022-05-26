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
	int clientsock;
	struct sockaddr_in clientadd;
	char buf[SIZE];
	int fd;

	(clientsock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0? printf("Error Creating Socket Instance\n") : printf("SOcket Created Successfully\n");

	memset(&clientadd,0,sizeof(clientadd));
	clientadd.sin_family=AF_INET;
	clientadd.sin_port=htons(8040);
	clientadd.sin_addr.s_addr=htonl(INADDR_ANY);
	(connect(clientsock,(struct sockaddr *)&clientadd,sizeof(clientadd)))<0? printf("Connection Error\n") : printf("Connected\n");

	memset(buf, 0x00, SIZE);
    printf("write file name to send to the server:  ");
    scanf("%s", buf);
    (fd = open(buf, O_RDONLY))<0 ? printf("Error Opening\n") : printf("File opened\n"); 

    memset(buf, 0, SIZE);
    int read_len = read(fd, buf, SIZE);
    send(clientsock, buf, read_len, 0);
    close(fd);
    close(clientsock);


}
