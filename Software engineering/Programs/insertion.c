//Author: Ankita Maity
//Assignment 1
//Program 2: Write a program to sort the elements of an array in increasing order using insertion sort
//9th February, 2018

#include <stdio.h>
#include <stdlib.h>
int main()
{
	int i,j,n,key;
	printf("Enter number of elements\n");
	scanf("%d",&n);
	int array[n];
	printf("Enter the elements\n");
	for(i=0;i<n;i++)
		scanf("%d", &array[i]);
	for(i=1;i<n;i++)
	{
		key=array[i];
		j=i-1;
		while(j>=0 && array[j]>key)
		{
			array[j+1]=array[j];
			j--;
		}
		array[j+1]=key;
	}	
	printf("The sorted array is:\n");		
	for(i=0;i<n;i++)
		printf("%d\t", array[i]);
	printf("\n");
}
