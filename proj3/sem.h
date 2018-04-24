#ifndef SEM_H
#define SEM_H


#include "thread.h"

//Semaphore data structure
//A value field and a queue of TCBs
typedef struct Semaphore
{
	int value;
	struct queue *tcbQueue;
}Semaphore;

void InitSem(Semaphore*, int);
void P(Semaphore*);
void V(Semaphore*);

//Initializes the value field with the specified value
void InitSem(Semaphore *sem, int value)
{	
	sem->tcbQueue = (struct queue*) malloc(sizeof(struct queue));
	initQueue(sem->tcbQueue);
	sem->value = value;
	return;
}

//decrements the semaphore
//if value < 0, then blocks the process in the queue associated with the semaphore
void P(Semaphore *sem)
{
	struct TCB_t *tcb;

	sem->value = sem->value - 1;
	if(sem->value < 0)
	{
		tcb = delQueue(runQ);
		addQueue(sem->tcbQueue, tcb);
		swapcontext(&(tcb->context), &(runQ->header->context));
	}
	return;
}

//increments the semaphore
//if value <= 0, takes TCB out of semaphore queue and puts it into the run queue
//NOTE: V also "yields" to the next runnable process
void V(Semaphore *sem)
{
	sem->value = sem->value + 1;
	if(sem->value <= 0)
	{
		addQueue(runQ, delQueue(sem->tcbQueue));
	}
	yield();
	return;
}


#endif
