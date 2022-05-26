//Author: Ankita Maity
//Assignment 2
//Program 3: Write a program to sort the elements in increasing order using selection sort
//16th February,2018

#include<stdio.h>
int main()
{
	int n,i,j,min,temp;
	printf("Enter the number of elements :\n");
	scanf("%d",&n);
	int a[n];
	printf("Enter the elements :\n");
	for(i=0;i<n;i++)
		scanf("%d",&a[i]);
	for(i=0;i<n-1;i++)
	{
		min=i;
		for(j=i+1;j<n;j++)
			if(a[j]<a[min])
				min=j;
		temp=a[min];
		a[min]=a[i];
		a[i]=temp;
	}
	for(i=0;i<n;i++)
		printf("%d\t",a[i]);
	printf("\n");
	return 0;
}
