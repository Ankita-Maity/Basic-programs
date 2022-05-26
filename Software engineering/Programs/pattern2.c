//Author: Ankita Maity
//Assignment 2
//Program 7: Write a program that will print a pyramid in stars
//16th February,2018

#include<stdio.h>
int main()
{
	int i,j,n;
	printf("Enter length of side\n");
	scanf("%d",&n);
	for (i=1; i<=n;i++)
		{
			for (j=1; j<=n-i;j++)
				printf(" ");
			for (j=1; j<2*i;j++)
				printf("*");
			printf("\n");
		}

	return 0;
}
