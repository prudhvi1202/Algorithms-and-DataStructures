
/*
Date: 30-5-2023
Author: K Prudhvi Raj.
Description: Shortest path of the Directed Acyclic Graph with Dijkstra Alogithms.
			Implmented wth Heap for Priority Queue.
			
			Time Complexity. O( ELogV) , Log V because of the Heap Delete Min and it's traversal
			for each edge Edge, I need to be clear to describe this Complexity properly.

			Some Extra details are also prints in the middle, if not required you can remove it.

INPUT:
Import HeapHeader.h into your code.
Number of Vertices and Edges as INPUT.

OUTPUT:
Distance Array-and from source to all nodes shortest path.
Path Array - to each node what is the immediate node we need to use.			
			
*/

#include "HeapHeader.h"
//#include<stdio.h>
//#include<stdlib.h>
void Heapify();
struct ListNode
{
	int vertex;
	int weight;
	int inque;
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
	G->Adj=(struct ListNode **)malloc(G->V*sizeof(struct ListNode*));
	for(i=0;i<G->V;i++)
	{
		G->Adj[i]=NULL;
	}	
	return G;
}
void addEdge(struct Graph *G,int s,int d,int wei)
{
	//printf("Entered Add Edge:\n");
	struct ListNode *temp=(struct ListNode *)malloc(sizeof(struct ListNode));
	temp->vertex=d;
	temp->weight=wei;
	temp->inque=0;
	//printf("weights are updated:\n");
	temp->next=G->Adj[s];//adding at the begining of the list 
	G->Adj[s]=temp;
//	printf("Value added %d",G->Adj[s]->vertex);
		
}
void displayQueue(int QueueA[],int front,int rear)
{
	int i;
	printf("\n");
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
struct ListNode *Head=NULL,*current=NULL;
void createNode(int NodeNo,int weight)
{
	//printf("\nCreateNode started:\n");
	struct ListNode *temp=(struct ListNode*)malloc(sizeof(struct ListNode));
	temp->vertex=NodeNo;
	temp->weight=weight;
	temp->next=NULL;
	if(Head==NULL)
	{
		//temp->next=Head;//creating at the beginning of the it'
		Head=temp;
		//current=temp;
		//printf("Element inserted is %d",temp->vertex);
	}
	else
	{
		//temp->next=NULL;
		current->next=temp;
		//printf("Element Insted is %d",temp->vertex);
		current=current->next;
	}
	printf("added the Node Successfully\n");
//	Heapify();
}

int InHeap(struct Heap *H,int ele)
{
	int i;
	for(i=0;i<H->count;i++)
	{
		if(H->array[i]==ele)
			return 1;		
	}
	return 0;
	
}
void Heapify2(struct Heap *h,int distance[])//can be improved, call two three times to heapify this.
{
	int i,j;
	for(i=0;i<=((h->count)-2)/2;i++)
	{
	//	printf("Entered working here:\n");
		if(2*i+1<=h->count && 2*i+2<=h->count)
		{
			if(distance[h->array[i]]<distance[h->array[2*i+1]] && h->heap_type==1)
			{
				swap(h,i,2*i+1);
			}
			else if(distance[h->array[i]]<distance[h->array[2*i+2]]&& h->heap_type==1)
			{
				swap(h,i,2*i+2);
			}
			else if(distance[h->array[i]]>distance[h->array[2*i+1]] && h->heap_type==0)
			{
				swap(h,i,2*i+1);
			}
			else if(distance[h->array[i]]>distance[h->array[2*i+2]]&& h->heap_type==0)
			{
				swap(h,i,2*i+2);
			}
		}
	}
}
void DijkstraFinalVersion2(struct Graph *G,int s)
{
	int distance[10]={999,999,999,999,999,999,999,999,999,999},path[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},i,QueueB[20],front=0,rear=0;
	struct Heap *H=CreateHeap(G->V,0);
	distance[s]=0;
	Hinsert(H,s);
	//Enqueue(QueueB,&rear,s);//instead of Enqueue create Node simple
	while(H->count!=0)
	{
		Hdisplay(H);
		//some redundant entries are happening in the Heap, but it is working fine.
		//displayQueue(QueueB,front,rear);
		int v=delete(H);
		//v=Dequeue(QueueB,&front,&rear);

		//printf("\nElement is : %d",v);
		struct ListNode *temp=G->Adj[v];

		while(temp)
		{
			if(!InHeap(H,temp->vertex))
			{
				Hinsert(H,temp->vertex);
				Heapify2(H,distance);
			//	path[temp->vertex]=v;
			}
			int d=distance[v]+temp->weight;
			if(distance[temp->vertex]==999)
			{
				distance[temp->vertex]=d;//changing this one line give possible distance
															//not shortest distance but possible distance.
				path[temp->vertex]=v;
			}
			else if(distance[temp->vertex]>d)
			{
				distance[temp->vertex]=d;
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
	struct ListNode *temp,*temp1;
	//printf("%d",G1->Adj[0]->vertex);	
	for(i=0;i<G1->V;i++)
	{
		temp=G1->Adj[i];
		//printf("vertex node values %d %d",temp->vertex,temp->next->vertex);
		//temp=temp1->next;
		printf("Vertex %d joined with",i);
		while(temp)
		{
			printf("(%d)->%d , ",temp->weight,temp->vertex);
			temp=temp->next;
		}
		printf("\n");
	}
}
int main()
{
	struct Graph *G1=adjListGraph();
//	struct Heap *H=CreateHeap(G1->V,0);
	int i;
	printf("This is Directed Acyclic Graph\n");
	addEdge(G1,0,1,3);
	addEdge(G1,0,5,2);
	addEdge(G1,0,3,5);
	addEdge(G1,1,2,3);
	addEdge(G1,2,4,0);
	addEdge(G1,3,4,1);
	addEdge(G1,4,6,2);
	addEdge(G1,5,6,6);
	addEdge(G1,5,2,1);
	addEdge(G1,5,4,2);	
	display(G1);
	DijkstraFinalVersion2(G1,0);
	return 0;
}
