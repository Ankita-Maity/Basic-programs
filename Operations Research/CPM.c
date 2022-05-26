#include<stdio.h>
int main()
{
 int i,j,k,m,p,count,n,f[10];
 float a[10][10],e[10],l[10],w,t;
 printf("Enter the no. of nodes:");
 scanf("%d",&n);
 printf("\nEnter network diagram and -1 to exit:");
 for(i=0;i<n;i++)
  for(j=0;j<n;j++)
	a[i][j]=0;
 while(1)
 {
  scanf("%d%d%f",&j,&k,&w);

  if(j==-1)
  break;
  a[j][k]=w;
 }
 e[0]=0;
 for(k=1;k<n;k++)
 {
  count=0;
  for(i=0;i<n;i++)
  {
	if(a[i][k]!=0)
	{
	 count++;
	 m=i;
	}
  }
  if(count==1)
	e[k]=e[m]+a[m][k];
  else
  {
  e[k]=0;
  for(i=0;i<n;i++)
	{
	 if(a[i][k]!=0)
	 {
	  t=e[i]+a[i][k];
	  if(t>e[k])
		e[k]=t;
	 }
	}
  }
 }
 l[n-1]=e[n-1];
 for(k=n-2;k>=0;k--)
 {
  count=0;
  for(j=0;j<n;j++)
  {
	if(a[k][j]!=0)
	{
	 count++;
	 p=j;
	}
  }
  if(count==1)
	l[k]=l[p]-a[k][p];
  else
  {
	l[k]=1000;
	for(j=0;j<n;j++)
	{
	 if(a[k][j]!=0)
	 {
	  t=l[j]-a[k][j];
	  if(t<l[k])
		l[k]=t;
	 }
	}
  }
 }
 for(i=1,k=0;i<n;i++)
 {
  if(e[i]==l[i])
	f[k++]=i;
 }
 printf("\nThe critical path is: 0");
 for(i=0;i<k;i++)
 printf("->%d",f[i]);
 return 0;
}
