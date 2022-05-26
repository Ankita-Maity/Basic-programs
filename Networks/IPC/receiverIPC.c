//Receiving the message previously sent

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
	msgrcv(msgid,&message,sizeof(message),10,0);
	printf("Message received: %s\n",message.mText);
	msgctl(msgid,IPC_RMID,NULL);
}
