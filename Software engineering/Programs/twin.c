//Author: Ankita Maity
//Assignment 3
//Program 11: Write a program to find all the twin primes upto a specific number entered by the user
//23rd February, 2018

#include<stdio.h>
int isprime (int n)
{
	int count=0,i;
	for (i=2; i<n; i++)
		if (n%i==0)
			count++;
	if (count==0)
		return 1;
	return 0;
}
int main()
{	int n;
	printf("Enter a number\n");
	scanf("%d",&n);
	int i=2;
	printf("Twin primes till %d:\n",n);
	while (i<=n-2)
		{if (isprime (i)==1 && isprime (i+2)==1)
			printf("%d %d\n", i, (i+2));
		i++;
		}
	
	return 0;
}

