#include <assert.h>
#include <stdlib.h>
#include "pqueue.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include "pack.h"
#include "assert.h"
#include <ctype.h>
#define END 256 
struct node *nodes[END+1];
int counts [END+1];

static struct node *mkNode(int data, struct node *left, struct node *right)
{
	struct node *np;
	np=malloc(sizeof(struct node)); 
	np->count = data;
	np->parent=NULL;

	if (left !=NULL)
		left->parent= np;

	if (right !=NULL)
		right->parent=np;

	return np;
}

static void readFile (char *Fname)
{
	FILE *fp; 
	int c=0;
	if ((fp= fopen(Fname, "r"))==NULL)
	{
		printf("File is empty"); 
		return;
	}
	while ((c=getc(fp)) != EOF)
		counts[c]++;
	return;
}
static int compare(struct node *left, struct node *right)
{
	if (left->count < right-> count)
		return -1;
	else if (left->count > right->count)
		return 1;
	else 
		return 0;

}

static int depth(struct node *Nodep)
{
	//base case
	if (Nodep->parent ==0)
		return 0;
	return 1+ depth(Nodep->parent);
	
}

int main(int argc, char *argv [])
{
	//make sure there are three files 
	if(argc !=3)
		return 0;
	int i; 
	for (i=0; i<257; i++)
	{
		counts[i]=0;
		nodes[i]=NULL;
	}
	
	readFile(argv[1]);
	struct pqueue *pq =createQueue(compare);
	
	//loop through counts array, if we have a valid count, then its greater than 0,then make it a node and add it into nodes array and into prirotity queue 
	
	for(i=0; i<256; i++)
	{
		//have a character that shows up at least once
		if(counts[i]>0) 
		{
			struct node *newNode= mkNode(counts[i], NULL, NULL);
			nodes[i]=newNode;
			addEntry(pq, nodes[i]);
		}
	}
	struct node *newNode= mkNode(0, NULL, NULL);
	nodes[END]=newNode;
	addEntry(pq, nodes[END]);
	while (numEntries(pq)>1)
	{
		struct node *left= removeEntry(pq);
		struct node *right=removeEntry(pq);
		struct node *parent=mkNode(left->count + right->count, left, right);
		addEntry(pq, parent);
	}
	//huffman tree is the last entry left
	for (i=0; i<=256; i++)
	{
		if(nodes[i] != NULL)
		{
			if (isprint(i))
			{
				printf("%c: %d x %d bits = %d bits\n",i, counts[i],depth(nodes[i]), depth(nodes[i]) *counts[i]  ); 
			}
			else
			{
				printf("%03o: %d x %d bits = %d bits\n",i, counts[i],depth(nodes[i]), depth(nodes[i])*counts[i]  );
			}
		}
	}
	pack(argv[1], argv[2], nodes); 
}
