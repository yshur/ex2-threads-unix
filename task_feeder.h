#ifndef TASK_FEEDER_H
#define TASK_FEEDER_H

#include "thread_pool_manager.h"

typedef struct	{
	void (*f)(void*);
	void* arg;
}task;

typedef struct	{
	TreadPoolManager* tpm;	
}task_feeder;

task* create_task(void (*f)(void*), void* arg);
task_feeder* task_feeder_init(TreadPoolManager* tpm);
void send_func_to_tfdr(task_feeder* tfdr, void (*f)(void*), void* arg);

#endif
