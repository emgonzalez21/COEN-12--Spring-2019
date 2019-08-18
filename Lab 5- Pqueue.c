
#include <assert.h>
#include <stdlib.h>
#include "pqueue.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include "assert.h"

#define P(x) (( (x)-1) / 2 ) //parent
#define L(x) (((x) * 2) + 1 ) //left
#define R(x) (((x) * 2) + 2) //right

struct pqueue 
{
	int count; 
	int length;
	int (*compare)();
	void **data;
 
};

//return a pointer to a new priority queue using compare as its comparison function
//O (1)
PQ *createQueue(int(*compare) ())
{
	
	PQ *pq;
	pq=malloc(sizeof(struct pqueue));
	assert (pq !=NULL);

	pq->length=10;
	pq->count=0; 

	pq->compare=compare;
	assert(compare !=NULL);

	pq->data=malloc(sizeof(void*) *pq->length);
	assert (pq->data !=NULL);
	
	return pq; 
}

//deallocate memory associated with the priority queue pointed to by pq
//O(1)
void destroyQueue (PQ *pq)
{
	
	assert (pq !=NULL);
	free (pq->data);
	free (pq);
}

//return the number of entries in the priority queue pointed to by pq
//O(1)
int numEntries(PQ *pq)
{

	assert(pq !=NULL);
	return pq->count;
}

//add entry to the priority queue pointed to by pq 
//O(logn)
void addEntry(PQ *pq, void *entry)
{
	
	assert (pq !=NULL);
	assert (entry !=NULL);

	if (pq->count == pq->length)
	{
		pq->length= pq->length*2;
		pq->data= realloc(pq->data, sizeof(void *) *pq->length);
		assert (pq->data !=NULL);
	}
    int index= pq->count++; 	
		while (index>0 && ((*pq->compare)(entry,pq->data[P(index)])) <0 )
		{
	
			pq->data[index]= pq->data[P(index)];
			index=P(index);		

		}
		pq->data[index]=entry;  
		return; 
	
}

//remove and return the smallest entry from the priority queue pointed to by pq
//O(logn)
void *removeEntry(PQ *pq)
{
	
	void *delete = pq->data[0];
	void *last= pq->data[--pq->count];
	int index=0;
	int child=0; 

	assert (pq !=NULL);
	while (L(index) < pq->count) //child within bounds
	{
		child=L(index);
		if(R(index) < pq->count)
		{
			if(pq->compare(pq->data[L(index)], pq->data[R(index)]) >0)
			{
				child=R(index);
			}
			
		}
		if (pq->compare(last,pq->data[child]) >0)
		{
		
			pq->data[index] =pq->data[child]; 
			index= child;
		}
		else 
		{
			break;
		}
	}
	pq->data[index]=last;
	return delete; 

}


