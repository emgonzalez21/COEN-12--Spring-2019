#include <assert.h>
#include <stdlib.h>
#include "list.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#define AVG_CHAIN_LENGTH 20 

struct set 
{
	int count; 
	int length;
	LIST **lists;
	int (*compare)();
	unsigned(*hash)(); 
};

typedef struct set SET;

SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)())
{
	SET *sp;
	int i; 
	sp= malloc(sizeof(SET)); 
	assert(sp !=NULL); 

	sp->length = maxElts/ AVG_CHAIN_LENGTH;
	sp->compare = compare; 
	sp->hash = hash;
	sp->count=0; 
	
	for(i=0; i<sp->length; i++)
	{
		sp->lists[i]=createList(compare); 
	}
	assert (sp->lists !=NULL);
	return sp; 
} 


void destroySet(SET *sp)
{
	free(sp->lists);
	free(sp);

}

int numElements (SET *sp)
{
	assert(sp !=NULL);
	return sp->count; 
}	

void addElement (SET *sp, void *elt)
{
	assert (sp !=NULL && elt !=NULL); 
	int index= (*sp->hash)(elt)%sp->length; 
	if (findItem(sp->lists[index],elt)==NULL)
	{
		addFirst(sp->lists[index],elt);
		sp->count++;
	}
}    	


void removeElement(SET *sp, void *elt)
{
	assert(sp !=NULL &&elt !=NULL);
	int index = (*sp->hash)(elt)%sp->length;
	if (findItem(sp->lists[index], elt) !=NULL)
	{
		removeItem(sp->lists[index],elt);
		sp->count--;
	}
}

void *findElement(SET *sp, void *elt)
{
	assert (sp !=NULL &&elt !=NULL);
	int index= (*sp->hash)(elt)%sp->length;
	return findItem(sp->lists[index], elt);
}

void *getElements(SET *sp)
{
	int i,j;
	assert (sp!=NULL);
	void **data2=malloc(sizeof(void*)*sp->count); 
	int count2=0;
	for (i=0; i<sp->length; i++)
	{
		void **copiedArray= getItems(sp->lists[i]);
		for (j=0; j<numItems(sp->lists[i]); j++)
		{
			data2[count2]=copiedArray[j];
			count2++;
		}
	}
	return data2; 
}
