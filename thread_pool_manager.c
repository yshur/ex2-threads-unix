#include "thread_pool_manager.h"
#include "task_feeder.h"

TreadPoolManager* PoolManagerInit(int num_of_threads)	{
	printf(" PoolManagerInit:\n");
	TreadPoolManager* tpm = (TreadPoolManager*)malloc(sizeof(TreadPoolManager));
	if (pthread_mutex_init(&(tpm->q_lock), NULL) != 0)
		perror(" PoolManagerInit:\t pthread_mutex_init");
	if (pthread_cond_init(&(tpm->q_cond), NULL) != 0)
		perror(" PoolManagerInit:\t pthread_cond_init");
	tpm->tskQueue = QueueInit(&(tpm->q_cond), &(tpm->q_lock));
	tpm->listOfThreads = create_list();

	for (int i=0; i<num_of_threads; i++)	{
		pthread_t* thread = (pthread_t*)malloc(sizeof(pthread_t));
		if(pthread_create(thread, NULL, waitingThread, tpm))
			return NULL;
		add_to_list(tpm->listOfThreads, thread);
		printf(" pthread_create:\t thread[%d] created succesfully\n", i);
	}	
	printf(" PoolManagerInit:\t ThreadPoolManager creates successfully\n");
	return tpm;
}

void* waitingThread(void* tpm)	{
	printf(" waitingThread:\n");
	TreadPoolManager* tpm_ptr = (TreadPoolManager*)tpm;
	task* tmp_task;
	Queue* tskq = tpm_ptr->tskQueue;
	for(;;)	{
		pthread_mutex_lock(&(tpm_ptr->q_lock));
		printf(" waitingThread:\t q_lock locked succesfully\n");
		while (tskq->head == NULL)	{
			pthread_cond_wait(&(tpm_ptr->q_cond), &(tpm_ptr->q_lock));
			printf(" waitingThread:\t head = NULL, waiting..\n");
		}
		tmp_task = (task*)deQueue(tskq);
		pthread_mutex_unlock(&(tpm_ptr->q_lock));
		printf(" waitingThread:\t q_lock unlocked succesfully\n");
		tmp_task->f(tmp_task->arg);
	}
}

void send_task_to_tpm(TreadPoolManager* tpm, void* x)	{
	printf(" send_task_to_tpm:\n");
	enQueue(x, tpm->tskQueue);
}
