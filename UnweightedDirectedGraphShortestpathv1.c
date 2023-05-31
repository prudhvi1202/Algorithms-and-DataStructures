/*
Title: Shortest Distance of Unweighted Directed Graph v1.
Author: K Prudhvi Raj.
Algorithm refence: (BOOK)Data Structures and Algorithms Made Easy .

INPUT: It takes the Number of Vertices and Edges, 
		All Edges are hard coding in main funciton.
		
		Source Vertex is also hard coded.
	
OUPTUT:
	Distance Array, from Source to all other Vertices are Nodes.
	
	Path Array. To reach each Node/Vertex, what is the immediate node to consider.


*/

#include<stdio.h>
#include<stdlib.h>
struct ListNode
{
	int vertex;
	//int inque;
	struct ListNode *next;
};

struct Graph
{
	int V;
	int E;
	struct ListNode **Adj;	
};
struct Graph *adjListGraph()
{
	int i,x,y;
	struct ListNode *temp;
	struct Graph *G=(struct Graph *)malloc(sizeof(struct Graph));
	if(!G)	
	{
		printf("Memory Error");
		return 0;
	}
	printf("Enter Number of Vertices and Edges\n");
	scanf("%d %d",&G->V,&G->E);
//	printf("Enter Number of Vertices and Edges %d %d\n",G->V,G->E);
	//Creating a array of vertieces to hold the linked list based on number of verties
	G->Adj=(struct ListNode **)malloc(G->V*sizeof(struct ListNode*));
	for(i=0;i<G->V;i++)
	{
		G->Adj[i]=NULL;//Initializing the Array pointers to NULL.
	}	
	return G;
}
void addEdge(struct Graph *G,int s,int d)
{
	struct ListNode *temp;
	temp=(struct ListNode *)malloc(sizeof(struct ListNode));
	temp->vertex=d;
	//indegree[d]=indegree[d]+1;// this one line calculate the indegree of the vertex
	//temp->inque=0;
	temp->next=G->Adj[s];//adding at the begining of the list 
	G->Adj[s]=temp;

/*I need Directed Acycic graph, so this edge is not needed		
	temp=(struct ListNode *)malloc(sizeof(struct ListNode));//if i typecast to that type, it is showing warning.
	temp->vertex=s;
	//temp->inque=0;
	temp->next=G->Adj[d]; //adding at the begining of the list.
	G->Adj[d]=temp;*/
	
}
void displayQueue(int QueueA[],int front,int rear)
{
	int i;
	for(i=front;i<rear;i++)
	{
		printf("%d\t",QueueA[i]);
	}
}
int isQueueEmpty(int front, int rear)
{
	if(front==rear &&front!=0)
		return 1;
	else
		return 0;
}
void Enqueue(int QueueA[], int *rear,int ele)
{
	QueueA[*rear]=ele;
	(*rear)++;
}
int Dequeue(int QueueA[],int *front,int *rear)
{
	
		int de=QueueA[*front];
		QueueA[*front]=-2;
		(*front)++;
		return de;
}
void displayindex(int size)
{
	int i;
	for(i=0;i<size;i++)
	{
		printf("%d\t",i);
	}
}
void shortestpath(struct Graph *G,int s)
{
	int distance[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},path[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},i,QueueB[20],front=0,rear=0;
	distance[s]=0;
	displayQueue(distance,0,G->V);
	Enqueue(QueueB,&rear,s);
	//printf("Queue is:");
	//displayQueue(QueueA,front,rear);
	while(!isQueueEmpty(front,rear))
	{
		int v=Dequeue(QueueB,&front,&rear);
		int x=v;
	//	printf("\nElement is : %d",v);
		struct ListNode *temp=G->Adj[v];
		//distance[x]=distance[x]+1;
		while(temp)
		{
			Enqueue(QueueB,&rear,temp->vertex);
			//displayQueue(QueueB,front,rear);
			//printf("%d index is ",temp->vertex);
			if(distance[temp->vertex]==-1)
			{
				distance[temp->vertex]=distance[v]+1;
				path[temp->vertex]=v;
			}
			temp=temp->next;
		}
	}
	printf("\nDisplaying Distance: \n");
	displayQueue(distance,0,G->V);
	printf("\n");
	displayindex(G->V);
	printf("\nPath is: \n");
	displayQueue(path,0,G->V);
	printf("\n");
	displayindex(G->V);
}
void display(struct Graph *G1)
{
	int i;
	struct ListNode *temp;	
	for(i=0;i<G1->V;i++)
	{
		temp=G1->Adj[i];
		//printf("vertex node values %d %d",temp->vertex,temp->next->vertex);
		printf("Vertex %d joined with",i);
		while(temp)
		{
			printf("->%d\t",temp->vertex);
			temp=temp->next;
		}
		printf("\n");
	}
}
int main()
{
	struct Graph *G1=adjListGraph();
	
	printf("This is Directed Acyclic Graph\n");
	addEdge(G1,0,1);
	addEdge(G1,0,3);
	addEdge(G1,2,0);
	addEdge(G1,2,5);
	addEdge(G1,1,3);
	addEdge(G1,1,4);
	addEdge(G1,3,6);
	addEdge(G1,3,5);
	addEdge(G1,4,6);
	addEdge(G1,6,5);
	display(G1);

	shortestpath(G1,2);
	return 0;
}
