#include<stdio.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>

void func(int s)
{char buff[100];
int n;
	for(;;)
	{bzero(buff,100);
	read(s,buff,sizeof(buff));
	printf("From client: %sServer: ",buff);
	bzero(buff,100);
	n=0;
	while((buff[n++]=getchar())!='\n');
	write(s,buff,sizeof(buff));
	if(strncmp("exit",buff,4)==0)
		{printf("Server Exit...\n");
		break;
		}
	}
}
int main()
{int soc,coc,len;
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
servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
servaddr.sin_port=htons(20020);
	if((bind(soc,(struct sockaddr *)&servaddr, sizeof(servaddr)))!=0)
	{printf("socket bind failed...\n");
	exit(0);
	}
	else
	printf("Socket successfully binded..\n");

	if((listen(soc,5))!=0)
	{printf("Listen failed...\n");
	exit(0);
	}
	else
	printf("Server listening..\n");

len=sizeof(cli);
coc=accept(soc,(struct sockaddr *)&cli,&len);
	if(coc<0)
	{printf("server acccept failed...\n");
	exit(0);
	}
	else
	printf("server acccept the client...\n");
func(coc);
close(soc);
}
