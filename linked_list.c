#include "linked_list.h"


linkedList* create_list()	{
	printf(" create_list:\n");
	linkedList* newList = (linkedList*)malloc(sizeof(linkedList));
	newList->head = newList->tail = NULL;
	newList->sizeOfList = 0;
	printf("create_list:\t list created successfully\n");
	return newList;
}

void add_to_list(linkedList* list, void* data)	{
	printf(" add_to_list:\n");
	node* newNode = (node*)malloc(sizeof(node));
	newNode->data = (void*)data;
	newNode->next = NULL;
	if(list == NULL)	{
		list = create_list();
	}
	if(list->head == NULL)	{
		list->tail = list->head = newNode;
	}
	else if(list->head != NULL)	{
		list->tail->next = newNode;
		list->tail = newNode;
	}
	printf(" add_to_list:\t node added successfully\n");
}

