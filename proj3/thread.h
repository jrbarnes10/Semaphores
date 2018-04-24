#ifndef THREADS_H
#define THREADS_H

#include "q.h"

//global header pointer
struct queue *runQ;

//forward declarations
void startThread(void (*function)(void));
void run();
void yield();

//allocate state, allocate tcb, call init_TCB, call addQ to add TCB into RunQ
void startThread(void (*function)(void)) {

	TCB_t *temp = newItem();
	void *stack = (void *) malloc(8192);

	init_TCB(temp, function, stack, 8192);
	addQueue(runQ, temp);

	return;
}

//starts thread
void run() {

	ucontext_t parent;
	getcontext(&parent);
	swapcontext(&parent, &(runQ->header->context));

	return;
}


void yield() {
	ucontext_t previousThread;
	getcontext(&previousThread);
	rotateQ(runQ);
	swapcontext(&previousThread, &(runQ->header->context));

	return;
}

#endif
