//Author: Ankita Maity
//Assignment 3
//Program 9: Write a program that will print a given pattern
//23rd February, 2018

#include<stdio.h>
int main()
{
	int i,j,n=4;
	for (i=1; i<=n;i++)
		{
			for (j=1; j<=n-i;j++)
				printf(" ");
			for (j=1; j<2*i;j++)
				printf("*");
			printf("\n");
		}
	for (i=1; i<=n;i++)
		{for(j=1;j<=7;j++)
			if(i!=n && j>2 && j<6)
				printf(" ");
			else
				printf("*");
		printf("\n");
		}

	return 0;
}
