#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
//#include <stdbool.h>

typedef struct	{
	void* data;
	struct Item* next;
}Item;

typedef struct	{
	Item* head;
	Item* tail;
	pthread_cond_t* qcond;
	pthread_mutex_t* qlock;
	int sizeOfQueue;
}Queue;

Queue* QueueInit(pthread_cond_t* qcond, pthread_mutex_t* qlock);
void enQueue(void* data, Queue* x);
void* deQueue(Queue* x);
//bool is_empty(Queue* x);
//int QueueSize(Queue* x);

#endif
