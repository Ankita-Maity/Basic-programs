//Author: Ankita Maity
//Assignment 2
//Program 5: Write a program to sort the elements in increasing order using quick sort
//16th February,2018


#include<stdio.h>
void sort(int a[],int beg,int end);
int part(int a[],int beg,int end);
int main()
{
	int n,i;
	printf("Enter the number of elements :\n");
	scanf("%d",&n);
	int a[n];
	for(i=0;i<n;i++)
		scanf("%d",&a[i]);
	sort(a,0,n-1);
	for(i=0;i<n;i++)
		printf("%d\t",a[i]);
	printf("\n");
	return 0;
}
void sort(int a[],int beg,int end)
{
	int loc;
	if(beg<end)
	{
		loc = part(a,beg,end);
		sort(a,beg,loc-1);
		sort(a,loc+1,end);
	}
}
int part(int a[],int beg,int end)
{
	int left,right,loc,temp,flag=0;
	left = loc = beg;
	right = end;
	while(flag != 1)
	{
	        while((a[loc] < a[right]) && loc != right) 
			right--;
		if(loc == right) 
			flag = 1;
		else if(a[loc] > a[right])
		{
			temp = a[loc];
			a[loc] = a[right];
			a[right] = temp;
			loc = right;
		}
		if(flag != 1)
		{
			while((a[loc] > a[left]) && loc != left) 
				left++;
			if(loc == left) 
				flag = 1;
			else if(a[loc] < a[left])
			{
				temp = a[loc];
				a[loc] = a[left];
				a[left] = temp;
				loc = left;
			}
		}
	}
	return loc;
}
