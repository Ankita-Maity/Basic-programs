//Author: Ankita Maity
//Assignment 3
//Program 8: Write a program that will test whether two words are anagrams (permutations of the same letter)
//23rd February, 2018

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{	printf("Enter the length of the words\n");
	int l,i,j; char temp;
	scanf("%d",&l);
	char w1[l],w2[l];
	printf("Enter the two words\n");
	scanf("%s",w1);
	scanf("%s",w2);
	
		for(i=0;i<l;i++)
		for (j=0; j<l;j++)
			{
			if((int)w1[j]>(int)w1[j+1])
				{
				temp=w1[j];
				w1[j]=w1[j+1];
				w1[j+1]=temp;
				}
			if((int)w2[j]>(int)w2[j+1])
				{
				temp=w2[j];
				w2[j]=w2[j+1];
				w2[j+1]=temp;
				}
			}	
	int flag=0;
	for(i=0;i<l;i++)
		if((int)w1[i]!=(int)w2[i])
			{printf("The words are not anagrams\n");	
			flag=1;
			break;
			}
	if(flag==0)
		printf("The words are anagrams\n");	
}
