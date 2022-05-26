//Sending a message
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct mm
{	long mType;
	char mText[880];
}mymsg;

void main()
{	char ch; int i=0;
	mymsg message; 
	message.mType=10;
	key_t key=ftok("test.txt",80);
	long msgid=msgget(key,0600|IPC_CREAT);
	printf("Enter a message: ");
	do 
	{       ch = getchar();
		message.mText[i++]=ch;
	} while(ch!='\n');
	msgsnd(msgid,&message,sizeof(message),0);
	printf("Message sent: %s\n",message.mText);
}
