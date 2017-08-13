#include "task_feeder.h"

task* create_task(void (*f)(void*), void* arg)	{
	printf(" create_task\n");
	task* new_task = (task*)malloc(sizeof(task));
	new_task->f = f;
	new_task->arg = arg;
	printf(" create_task:\t new_task was created\n");
	return new_task;
}

task_feeder* task_feeder_init(TreadPoolManager* tpm)	{
	printf(" task_feeder_init:\n");
	task_feeder* tfdr = (task_feeder*)malloc(sizeof(task_feeder));
	tfdr->tpm = tpm;
	printf(" task_feeder_init:\t task_feeder was created\n");
	return tfdr;
}

void send_func_to_tfdr(task_feeder* tfdr, void (*f)(void*), void* arg)	{
	printf(" send_func_to_tfdr:\n");
	task* new_task = create_task(f, arg);
	send_task_to_tpm(tfdr->tpm, new_task);
	printf(" send_func_to_tfdr:\t new_task send to tpm successfully\n");
}
