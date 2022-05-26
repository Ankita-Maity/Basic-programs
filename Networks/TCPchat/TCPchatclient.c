#include<stdio.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
void func(int soc)
{
	char buff[100];
	int n;
	for(;;)
	{bzero(buff,sizeof(buff));
	printf("Client: ");
	n=0;
	while((buff[n++]=getchar())!='\n');
	write(soc,buff,sizeof(buff));
	bzero(buff,sizeof(buff));
	read(soc,buff,sizeof(buff));
	printf("From Server : %s",buff);
	if((strncmp(buff,"exit",4))==0)
		{printf("Client Exit...\n");
		break;
		}
	}
}
int main()
{	int soc,coc;
	struct sockaddr_in servaddr,cli;
	soc=socket(AF_INET,SOCK_STREAM,0);
	if(soc==-1)
		{printf("socket creation failed...\n");
		exit(0);
		}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servaddr.sin_port=htons(20020);
	if(connect(soc,(struct sockaddr *)&servaddr,sizeof(servaddr))!=0)
		{printf("connection with the server failed...\n");
		exit(0);
		}
	else
		printf("connected to the server..\n");
	func(soc);
	close(soc);
}

