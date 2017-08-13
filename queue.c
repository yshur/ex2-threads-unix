#include "queue.h"

Queue* QueueInit(pthread_cond_t* qcond, pthread_mutex_t* qlock)	{
	printf(" QueueInit:\n");
	Queue* new = (Queue*)malloc(sizeof(Queue));
	new->head = new->tail = NULL;
	new->qcond = qcond;
	new->qlock = qlock;
	new->sizeOfQueue = 0;
	printf(" Queueinit:\t Queue was inited successfully\n");
	return new;
}

void enQueue(void* data, Queue* x)	{
	printf(" enQueue:\n");
	pthread_mutex_lock((x->qlock));
	printf(" enQueue:\t Queue's lock loecked successfully\n");
	Item* newItem = (Item*)malloc(sizeof(Item));
	newItem->data = data;
	newItem->next = NULL;
	if (x->tail == NULL)	{
		x->tail = newItem;
		x->head = x->tail;
	}
	else	{
		Item* p = x->tail;
		p->next = (struct Item*)newItem;
		x->tail = newItem;
	}
	printf(" enQueue:\t newItem enQueued successfully\n");
	(x->sizeOfQueue)++;
	pthread_cond_signal((x->qcond));
	pthread_mutex_unlock((x->qlock));
	printf(" enQueue:\t qlock & qcond unlocked\n");
}

void* deQueue(Queue* x)	{
	printf(" deQueue:\n");
	Item* p = x->head;
	void* data = p->data;
	x->head = (Item*)p->next;
	x->sizeOfQueue--;
	printf(" deQueue:\t size of queue = %d\n", x->sizeOfQueue);
	return data;
}


