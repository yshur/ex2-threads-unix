
/* Program to compute Pi using Monte Carlo methods */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "queue.h"
#include "thread_pool_manager.h"
#include "task_feeder.h"
#include "linked_list.h"

#define SEED 35791246

typedef struct	{
	int* hits;
	int num_of_tries;
	int* end;
}mk_arg;

mk_arg* mk_arg_init(int num_of_tries);
void monte_carlo(void* p);

int main(int argc, char* argv[])
{
	int num_of_tries, num_of_threads;
	int count=0, end=0;
	double pi=0;

	int num_of_tasks;
	int tries_per_task;
	mk_arg* args;
	node* temp;
	linkedList* list_of_args;
	TreadPoolManager* tpm;
	task_feeder* tfdr;

	int i;

	if (argc != 3)	{
	    fprintf(stderr,"usage: main_app num_of_tries num_of_threads\n");
	    exit(1);
	}

	num_of_tries = strtol(argv[1], NULL, 10);
	num_of_threads = atoi(argv[2]);
	printf("enter num of tasks\n");
	scanf("%d", &num_of_tasks);
	tries_per_task = num_of_tries/num_of_tasks;

	printf(" main:\n num_of_tries = %d\n num_of_threads = %d\n num_of_tasks = %d\n tries_per_task = %d\n", num_of_tries, num_of_threads, num_of_tasks, tries_per_task);

	tpm = PoolManagerInit(num_of_threads);
	list_of_args = create_list();
	tfdr = task_feeder_init(tpm);

	for(i=0; i<num_of_tasks; i++)	{
		args = mk_arg_init(tries_per_task);
		add_to_list(list_of_args, (void*)args);
		send_func_to_tfdr(tfdr, monte_carlo, (void*)args);
	}

	while(end<num_of_tasks)	{
		//sleep(1);
		count=end=0;
		for(temp=list_of_args->head; temp!=NULL; temp=temp->next)	{
			args = (mk_arg*)temp->data;
			count = count+(*(args->hits));
			end += *(args->end);
		}
	}
 
	printf(" back to main:\n");
	printf(" count = %d, num_of_tries = %d, count/num_of_tries = %lf\n", count, num_of_tries, (double)count/num_of_tries);

   pi = (double)count/num_of_tries*4;
   printf("# of trials= %d, estimate of pi is %g \n", num_of_tries ,pi);

	return 0;
}

mk_arg* mk_arg_init(int num_of_tries)	{
	printf(" mk_arg_init:\n");
	mk_arg* monte_karlo_args = (mk_arg*)malloc(sizeof(mk_arg));
	monte_karlo_args->hits = (int*)malloc(sizeof(int));
	*(monte_karlo_args->hits) = 0;
	monte_karlo_args->num_of_tries = num_of_tries;
	monte_karlo_args->end = (int*)malloc(sizeof(int));
	*(monte_karlo_args->end) = 0;
	printf(" mk_arg_init:\t hits = %d, num_of_tries = %d, end = %d\n", *(monte_karlo_args->hits), monte_karlo_args->num_of_tries, *(monte_karlo_args->end));
	return monte_karlo_args;
}

void monte_carlo(void* p)	{
	printf(" monte_carlo:\n");
	double x, y, z;
	int i=0;
	mk_arg *ptr = (mk_arg*)p;
	srand(SEED);
	*(ptr->hits)=0;
	for (i=0; i<ptr->num_of_tries; i++)	{
		x = (double)rand()/RAND_MAX;
    	y = (double)rand()/RAND_MAX;
    	z = x*x+y*y;
    	if (z<=1)
			 *(ptr->hits) += 1;
		//	printf("count++\n");

    }
	printf(" count = %d, tries = %d\n", *(ptr->hits), i);
	*(ptr->end) = 1;
}


