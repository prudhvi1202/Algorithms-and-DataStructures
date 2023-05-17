/*
This C Code Create Undirected Graph with Adjecncy list
INPUT: reads Number of Vertices and Edges
		hard code(edit in the Main section of the Code
		to aadd all edges, Because this process is much easy 
		then reading at runtime.
OUTPUT:
	DFS(Depth First Search) with Stack(Implemented with Array).
	BFS(Breadth First Search) with Queue(Implemented with Array.
	Call the required function Accordingly.
*/

#include<stdio.h>
#include<stdlib.h>

struct ListNode
{
	int vertex;    //Vertex Number
	struct ListNode *next; //next vertex address needed in Adjecncy list
};
struct Graph
{
	int V;   // to hold number of vertices
	int E;    //to hold number of edges
	struct ListNode **Adj;	//to hold the address of all the linked list addrresses
};
struct Graph *adjListGraph()
{
	int i,x,y;
	struct ListNode *temp;
	struct Graph *G=(struct Graph *)malloc(sizeof(struct Graph));
	if(!G)	
	{
		printf("Memory Error");
		return;
	}
	printf("Enter Number of Vertices and Edges\n");
	scanf("%d %d",&G->V,&G->E);
	G->Adj=malloc(G->V*sizeof(struct ListNode*));
	for(i=0;i<G->V;i++)
	{
		G->Adj[i]=NULL;
	}	
	return G;
}
void addEdge(struct Graph *G,int s,int d)
{
	struct ListNode *temp;
	temp=(struct ListNode *)malloc(sizeof(struct ListNode));
	if(G->Adj[s]==NULL)// to hold the first element of the linked list 
		temp->next=NULL;
	temp->vertex=d;
	temp->next=G->Adj[s];//adding at the begining of the list everytime
	G->Adj[s]=temp;

		
	temp=(struct ListNode *)malloc(sizeof(struct ListNode));//if i typecast to that type, it is showing warning.
	if(G->Adj[d]==NULL) //undirected so adding reverse Edge also.
		temp->next=NULL;
	temp->vertex=s;
	//temp->inque=0;
	temp->next=G->Adj[d]; 
	G->Adj[d]=temp;
	
}
void push(int stackA[],int size,int *top,int ele)//stack push function
{
	if(*top==size)
	{
		printf("Stack Full can't insert'");
		return;
	}
	*top=*top+1;//top also global variable.
	stackA[*top]=ele;//making the stackA global
//	printf("Inseted Element %d\n",ele);
}
int pop(int stackA[],int *top)//stack pop function.
{
	int re;
	//printf("received top is %d",*top);
	if(*top==-1) //top as global variable.
	{
		printf("Stack Empty can't pop anymore");
		return 0;
	}
	re=stackA[*top];
	*top=*top-1;
	return re;
}
int isStackEmpty(int stackA[],int top)
{
	if(top==-1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void DFSTraversal(struct Graph *G,int u)
{
	int Visited[20]={0},stackA[10],size=10,top=-1;//just because i didn't initialize the values,
								//this visited array takeing random values and disturbed my code.
	Visited[u]=1;
	push(stackA,size,&top,u);
	while(isStackEmpty(stackA,top)==0)
	{
		int re=pop(stackA,&top);
		Visited[re]=1;
		
		printf("%d\t",re);
		struct ListNode *temp=G->Adj[re];
		while(temp)
		{
			//printf("\nin linked list temp vertex value is %d\n",temp->vertex);
			//printf("Content of the Visisted[temp->vertex] %d\n",Visited[temp->vertex]);
			if(Visited[temp->vertex]==0)
			{
				//printf("Inside Visited node");
				push(stackA,size,&top,temp->vertex);
			}
			temp=temp->next;
		}
		//printf("IsStackEmpty %d\n",isStackEmpty(stackA,top));
	}
}
int isQueueEmpty(int front, int rear)
{
	if(front==rear && front!=0)
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
		QueueA[*front]=0;
		(*front)++;
		return de;
}
void BFSTraversal(struct Graph *G,int u)
{
	int QueueA[20]={0},front=0,rear=0,Visited[20]={0};
	Enqueue(QueueA,&rear,u);
	//G->Adj[u]->inque=1;
	while(!isQueueEmpty(front,rear))
	{
		int re=Dequeue(QueueA,&front,&rear);
		printf("%d\t",re);
		Visited[re]=1;
		struct ListNode *temp=G->Adj[re];
		while(temp)
		{
			if(!Visited[temp->vertex])
			{
			//	printf("Vetex Number is %d",temp->vertex);
				Enqueue(QueueA,&rear,temp->vertex);
			}
			temp=temp->next;
		}
	}
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

}void main()
{
	struct Graph *G1=adjListGraph();
	int i;
	addEdge(G1,0,1);
	addEdge(G1,2,0);
	addEdge(G1,1,3);
	addEdge(G1,2,4);
	printf("Graph Structure:\n");
	display(G1);
	printf("DFS Traversal is \n");
	DFSTraversal(G1,1);
	printf("\nBFS Traversal is \n");
	BFSTraversal(G1,1);
}
