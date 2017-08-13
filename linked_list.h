#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t	{
	void* data;
	struct node_t* next;
}node;

typedef struct	{
	node* head;
	node* tail;
	int sizeOfList;
}linkedList;

linkedList* create_list();
void add_to_list(linkedList* list, void* data);

#endif
