#include<stdio.h>
#include<string.h>
#include<math.h>

#define INF 32767
#define N 26
#define B 5


int Dijkstra(int weight[][N], int source, int target);
int main()
{
    int weight[N][N],i,j,w,finaldist;
    int source,target,u,v;

    for(i=1;i< N;i++)
    {
        for(j=1;j< N;j++)
        {
            weight[i][j] = INF; //initially sab ko infinity se initialize kar de
        }
    }

    for(u=1;u< N;u++)
    {
    if(u%B!=0)
    {
     	    v=u+1;
            printf("Enter the value between nodes %d and %d: ",u,v);
            scanf("%d",&w);
            weight [u][v] = w;
            weight [v][u] = w;
	    if(u<N-B)
	    {
	        v=u+B;
            printf("Enter the value between nodes %d and %d: ",u,v);
            scanf("%d",&w);
            weight [u][v] = w;
            weight [v][u] = w;
	    }
    }
    else
    {
	   if(u<N-B)
	    {
	    v=u+B;
	    printf("Enter the value between nodes %d and %d: ",u,v);
	    scanf("%d",&w);
	    weight[u][v] = w;
        weight[v][u] = w;
	    }
    }
    
        printf("\n");
    }

    source=1;    
    target=N-1;

    finaldist = Dijkstra(weight,source,target);
    printf("\nThe Final Weight: %d\n",finaldist);
}

int Dijkstra(int weight[][N],int source,int target)
{
    int dist[N],prev[N],visited[N],i;
    for(i=0;i<N;i++)
    {
        visited[i]=0;
    }
    int min,currentNode,distance,temp;
    
    int path[N];
    for(i=1;i< N;i++)
    {
        dist[i] = INF;
        prev[i] = -1;
    }

    currentNode = source;
    visited[currentNode]=1;
    dist[currentNode] = 0;
    while(visited[target]==0)
    {
        min = INF;
        temp = 0;
        for(i=1;i< N;i++)
        {
            distance = dist[currentNode] + weight[currentNode][i];
            if(distance< dist[i] && visited[i]==0) //agar distance is less than what was previously marked on the node, toh hum update kar denge
            {
                dist[i] = distance; 
                prev[i] = currentNode;
            }
            if(dist[i]<min && visited[i]==0)
            {
                min = dist[i];
                temp = i; //to keep record of the node number
            }
        }
        currentNode = temp;
        visited[currentNode] = 1; //mark node as visited
    }
    currentNode = target;
    
    int j = 0;
    while(currentNode != -1) //source ka prev abhi bhi -1 hai
    {
        path[j] = currentNode; //traverse in reverse the prev of each currentNode
        j++;
        currentNode = prev[currentNode];
    }

    printf("The shortest path is: \n");
    for(i=j-1;i>0;i--)
    {
        printf("%d-->", path[i]);
    }
    printf("%d",N-1);
    return dist[target];
}
