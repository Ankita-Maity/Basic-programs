#include<stdio.h>
#define INFINITY 9999
#define MAX 10
 
void dijkstra(int G[MAX][MAX],int n,int startnode);
 
int main()
{
    int G[MAX][MAX],i,j,n,u;
    printf("Enter no. of vertices:\n");
    scanf("%d",&n);
    printf("Enter the adjacency matrix:\n");
    
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            scanf("%d",&G[i][j]);
    
    printf("Enter the starting node:\n");
    scanf("%d",&u);
    dijkstra(G,n,u);
    
    return 0;
}
 
void dijkstra(int G[MAX][MAX],int n,int startnode)
{
 
    int cost[MAX][MAX],count,mindistance,nextnode,i,j;

    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(G[i][j]==0)
                cost[i][j]=INFINITY;
            else
                cost[i][j]=G[i][j];
int distance[MAX],pred[MAX];
    int visited[MAX];
    
    for(i=0;i<n;i++)
    {
        distance[i]=cost[startnode][i];
        pred[i]=startnode;
        visited[i]=0;
    }
    
    distance[startnode]=0;
    visited[startnode]=1;
    count=1;
    
    while(count<n-1)
    {
        mindistance=INFINITY;
        for(i=0;i<n;i++)
            if(distance[i]<mindistance&&!visited[i])
            {
                mindistance=distance[i];
                nextnode=i;
            }          
            visited[nextnode]=1;
            for(i=0;i<n;i++)
                if(!visited[i])
                    if(mindistance+cost[nextnode][i]<distance[i])
                    {
                        distance[i]=mindistance+cost[nextnode][i];
                        pred[i]=nextnode;
                    }
        count++;
    }
    for(i=0;i<n;i++)
        if(i!=startnode)
        {
            printf("Distance of node %d= %d\n",i,distance[i]);
            printf("Path=%d ",i);
            
            j=i;
            do
            {
                j=pred[j];
                printf("<- %d",j);
            }while(j!=startnode);
		printf("\n");
    }
}
