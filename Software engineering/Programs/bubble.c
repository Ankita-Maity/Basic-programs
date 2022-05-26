//Author: Ankita Maity
//Assignment 1
//Program 1: Write a program to sort the elements of an array in increasing order using bubble sort
//9th February, 2018

#include <stdio.h>
#include <stdlib.h>
int main()
{
	int i,j,n,temp;
	printf("Enter number of elements\n");
	scanf("%d",&n);
	int array[n];
	printf("Enter the elements\n");
	for(i=0;i<n;i++)
		scanf("%d", &array[i]);
	for(i=0;i<n;i++)
		for (j=0; j<n;j++)
			if(array[j]>array[j+1])
				{
				temp=array[j];
				array[j]=array[j+1];
				array[j+1]=temp;
				}	
	printf("The sorted array is:\n");		
	for(i=0;i<n;i++)
		printf("%d\t", array[i]);
	printf("\n");
}
