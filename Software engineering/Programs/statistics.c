//Author: Ankita Maity
//Assignment 3
//Program 10: Write a program to find mean, median, mode and range of some elements
//23rd February, 2018

#include<stdio.h>
int main()
{
	int n,i,j,temp;
	printf("How many numbers will you enter?\n");
	scanf("%d",&n);
	int arr[n];
	printf("Enter the numbers\n");
	for(i=0; i<n; i++)
		scanf("%d",&arr[i]);
	for(i=0;i<n;i++)
		for (j=0; j<n;j++)
			if(arr[j]>arr[j+1])
				{
				temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
				}	
	int mode,range=arr[n-1]-arr[0]; double median=0.0, mean=0.0;
	int freq=1,freq1=1;
	for(i=0;i<n;i++)
		mean+=arr[i];
	mean=mean/n;
	for(i=1;i<n;i++)
		{if(arr[i-1]==arr[i])
			freq1++;
		else freq1=1;
		if(freq1>freq)
			{freq=freq1;
			mode=arr[i];
			}
		}
	if(n%2==1)
		median=arr[n/2];
	else
		median=(arr[n/2]+arr[(n/2)-1])/2.0;
	printf ("mean=%f median=%f mode=%d range=%d\n", mean,median,mode,range);
	return 0;
}
