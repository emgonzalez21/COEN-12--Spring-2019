#include <assert.h>
#include <stdlib.h>
#include "list.h"
#include <string.h>
#include <stdbool.h>

struct list 
{
	int count; //counter
	struct node *head;//head pointer
	int (*compare)();//function pointer
};

typedef struct list LIST;
struct node 
{
	void *data;
	struct node *next; 
	struct node *prev;
};

//return a pointer to a new list using compare as its comparison function, which may be NULL 
LIST *createList(int (*compare)())
{
	LIST *lp;
	lp= malloc(sizeof(struct list)); 
	assert(lp !=NULL);
	lp->count=0;
   	
	lp->compare=compare; 

	lp->head=malloc(sizeof(struct node)); 
	assert (lp->head !=NULL);
	lp->head->prev = lp->head; 
	lp->head->next = lp->head;

	return lp; 
} 

//deallocate memory associated with the list pointed to by lp
void destroyList(LIST *lp)
{
	struct node *np, *next; 
	assert(lp !=NULL);
	np= lp->head;
	do
	{
		next= np->next;
		free(np);
		np= next;
	}
	while (np!=lp->head);
		free(lp);
}

//return the number of items in the list pointed to by lp
int numItems (LIST *lp)
{
	assert(lp !=NULL);
	return lp->count; 
}	

//add item as the first item in the list pointed to by lp
void addFirst (LIST *lp, void *item)
{
	struct node *np, *dummy=lp->head; 
	assert (lp !=NULL); 

	np=malloc(sizeof(struct node)); 
	assert (np !=NULL);
	
	np->data = item; 
	
	np->prev=dummy;
	np->next=dummy->next;


	dummy->next->prev= np; 
	dummy->next= np;

	lp->count++; 

}    	


//add item as the last item in the list pointed to by lp
void addLast(LIST *lp, void *item)
{
	struct node *np, *dummy=lp->head;
	assert (lp !=NULL);
	np=malloc(sizeof(struct node));
	assert (np !=NULL);
	
	np->data= item;

	np->prev= dummy->prev; 
	np->next= dummy; 

	dummy->prev->next= np; 
	dummy->prev=np; 
	
	lp->count ++;
	
}


//remove and return the first item in the list pointed to by lp; the list must not be empty
void *removeFirst (LIST *lp)
{
	struct node *dummy, *pDel;
	assert (lp !=NULL);
	
	dummy=lp->head; 
	pDel=dummy->next;
	dummy->next=pDel->next;

	pDel->next->prev=dummy; 

	void *item= pDel->data;
	free(pDel); 
	lp->count--;
	return item;
	
}

//remove and return the last item in the list pointed to by lp; the list must not be empty
void *removeLast(LIST *lp)
{
	struct node *dummy, *pDel;
	assert (lp !=NULL);
	
	dummy= lp->head;
	pDel=dummy->prev;
	dummy->prev=pDel->prev;

	pDel->prev->next=dummy;
 	
	void *item= pDel->data;
	free(pDel);
	lp->count--;
	return item;

}
//return, but do not remove, the first item in the list pointed to by lp' the list must not be empty 
void *getFirst(LIST *lp)
{
	struct node *dummy;
	assert (lp!=NULL);
	dummy= lp->head;
	
	void *item=dummy->next->data;
	return item;
	
}
//return, but do not remove, the last item in the list pointed to by lp' the list must not be empty 
void *getLast(LIST *lp)
{
	struct node *dummy; 
	assert (lp!=NULL);
	dummy=lp->head; 

	void *item= dummy->prev->data;
	return item;
}

//if item is present in the list pointed to by lp then remove it; the comparion function must not be NULL
void removeItem(LIST *lp, void *item)
{
	assert (lp!=NULL);
	struct node *i; 
	
	for (i=lp->head->next; i != lp->head; i= i->next)
	{
		if ((*lp->compare)(i->data,item)==0)
		{
			i->prev->next = i->next;
			i->next->prev=i->prev;
			lp->count--;
			free(item); 
			break; 	
		}
	}
	return;

}

//if item is present in the list pointed to by lp then return the matching item, otherwise return NULL; the comparison function must not be NULL
void *findItem(LIST *lp, void *item)
{
	assert (lp!=NULL);
	struct node *i;
	for(i=lp->head->next; i!= lp->head; i= i->next)
	{
		if ((*lp->compare)(i->data, item)==0)
			return i->data;
	}
	return NULL;
}
//allocate and return an array of items in the list pointed to by lp
void *getItems(LIST *lp)
{
	void **data2=malloc(sizeof(void*)*lp->count); 
	struct node *i;
	int j=0;
	assert (lp !=NULL);
	for (i=lp->head->next; i != lp->head; i=i->next)
	{
		data2[j]=i->data; 
		j++; 

	}
	return data2; 

}
