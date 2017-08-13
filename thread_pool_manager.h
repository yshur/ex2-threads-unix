#ifndef THREAD_POOL_MANAGER_H
#define THREAD_POOL_MANAGER_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#include "queue.h"
#include "linked_list.h"

typedef struct	{
	pthread_mutex_t q_lock;
	pthread_cond_t q_cond;
	Queue* tskQueue;
	linkedList* listOfThreads;
}TreadPoolManager;

TreadPoolManager* PoolManagerInit(int num_of_threads);
void* waitingThread(void* tpm);
void send_task_to_tpm(TreadPoolManager* tpm, void* x);

#endif
