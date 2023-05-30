/*
Date: 30-05-2023
Author: K P Raj
Description: This header file contains Function realted to Heap Data Structure/Priority Queue
			CreateHeap, Heapity, Hinsert, Finding ParentNode, VerifyHeap.
			
			Import into your code, check the function prototype and call accordingly.


*/

#include<stdio.h>
#include<stdlib.h>
//Heap Data Structure
struct Heap
{
	int *array; //Array along with some other associated varaibles, we can create
				//as the userdefined data type.
	int count; //i think for indexing the array of the heap
	int capacity;//maximum elements that we can store in the Heap.
	int heap_type;//0 min heap, 1 max heap
};
struct Heap* CreateHeap(int capacity, int heap_type)
{
	struct Heap *h=(struct Heap *)malloc(sizeof(struct Heap));
	if(h==NULL)
	{
		printf("memeory error");
		return;
	}
	h->capacity=capacity;
	h->heap_type=heap_type;
	h->count=0;
	h->array=(int* )malloc(sizeof(int)*h->capacity);
	if(h->array==NULL)
	{
		printf("Memory Error");
		return;
	}
	return h;
}
void swap(struct Heap *h,int loc1, int loc2)
{
	int temp;
	temp=h->array[loc1];
	h->array[loc1]=h->array[loc2];
	h->array[loc2]=temp;
}
void Heapify(struct Heap *h)//can be improved, call two three times to heapify this.
{
	int i,j;
	for(i=0;i<=((h->count)-2)/2;i++)
	{
		if(2*i+1<=h->count && 2*i+2<=h->count)
		{
			if(h->array[i]<h->array[2*i+1] && h->heap_type==1)
			{
				swap(h,i,2*i+1);
			}
			else if(h->array[i]<h->array[2*i+2]&& h->heap_type==1)
			{
				swap(h,i,2*i+2);
			}
			else if(h->array[i]>h->array[2*i+1] && h->heap_type==0)
			{
				swap(h,i,2*i+1);
			}
			else if(h->array[i]>h->array[2*i+2]&& h->heap_type==0)
			{
				swap(h,i,2*i+2);
			}
		}
	}
}
//use this to add elements to the heap, if required, every insertion we can apply heapify
//to make sure it always satisfy the Heap properties
void Hinsert(struct Heap *h,int ele)
{
	if(h->count<=h->capacity)
	{
		h->array[h->count]=ele;
		h->count=h->count+1;
	}
	else
	{
		printf("Array Full\n");
	}
//	Heapify(h);
}
int parentNode(struct Heap *h,int loc)
{
	if(loc<=0 || loc>=h->count)
		return -1;
	else
		return (loc-1)/2;
}
int delete(struct Heap *h)
{
	int temp;
	temp=h->array[0];
	swap(h,0,h->count-1);
	h->array[h->count-1]=(int)NULL;
	h->count=h->count-1;
	printf("\nDelelted Element is %d\n",temp);	
	return temp;
}
int verifyHeap(struct Heap *h)
{
	int i,flag=1;
	for(i=0;i<=(h->count-1)/2;i++)
	{
		if(h->heap_type==1)
		{
			if(h->array[i]<h->array[2*i+1] || h->array[i]<h->array[2*i+2])
				return 0;
			else
				return flag;
		}
		if(h->heap_type==0)
		{
			if(h->array[i]>h->array[2*i+1] || h->array[i]>h->array[2*i+2])
				return 0;
			else
				return flag;
		}
		
	}
}
int isHeapEmpty(struct Heap *h)
{
	if(h->count=0)
		return 1;
	else
		return 0;
}
void Hdisplay(struct Heap *h)
{
	printf("Details of the created heap\n");
	if(h->heap_type==0)
		printf("The Heap is Min Heap\n");
	else
		printf("The heap is Max Heap\n");
	printf("Capacity of it is %d\n",h->capacity);

	int i;
	printf("Elements in the Array are :\n");

	for(i=0;i<h->count;i++)
	{
		printf("%d\t",h->array[i]);
	}	
	printf("\n");
	for(i=0;i<h->count;i++)
	{
		printf("%d\t",i);
	}
	printf("\n");
}

