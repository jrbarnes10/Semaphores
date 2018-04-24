//Josh Barnes
//Project 2
//CSE330

#include "sem.h"
#include <stdio.h>

#define N 5

void producer1();
void producer2();
void consumer1();
void consumer2();

struct Semaphore *full;
struct Semaphore *empty;
struct Semaphore *mutex;
int buff[N];
int in = 0;
int out = 0;
int item =1;


void producer1()
{
	while(1){
		P(empty);
		P(mutex);
		buff[in] = 1;
		in = (in + 1) % N;
		printf("PRODUCER 1 \n Buff[0]: %d\t Buff[1]: %d\t Buff[2]: %d\t Buff[3]: %d\t Buff[4]: %d\n", buff[0], buff[1], buff[2], buff[3], buff[4]);
		sleep(1);
		V(mutex);
		V(full);
	}
	return;
}

void producer2()
{
	while(1){
		P(empty);
		P(mutex);
		buff[in] = 1;
		in = (in) % N;
		printf("PRODUCER 2 \n Buff[0]: %d\t Buff[1]: %d\t Buff[2]: %d\t Buff[3]: %d\t Buff[4]: %d\n", buff[0], buff[1], buff[2], buff[3], buff[4]);
		sleep(1);
		V(mutex);
		V(full);
	}
	return;
}

void consumer1()
{
	while(1){
		P(full);
		P(mutex);
		buff[out] = 0;
		out = (out + 1) % N;
		printf("CONSUMER 1 \n Buff[0]: %d\t Buff[1]: %d\t Buff[2]: %d\t Buff[3]: %d\t Buff[4]: %d\n", buff[0], buff[1], buff[2], buff[3], buff[4]);
		sleep(1);		
		V(mutex);
		V(empty);
	}
	return;
}

void consumer2()
{
	while(1){
		P(full);
		P(mutex);
		buff[out] = 0;
		out = (out + 1) % N;
		printf("CONSUMER 2 \n Buff[0]: %d\t Buff[1]: %d\t Buff[2]: %d\t Buff[3]: %d\t Buff[4]: %d\n", buff[0], buff[1], buff[2], buff[3], buff[4]);
		sleep(1);		
		V(mutex);
		V(empty);
	}
	return;
}

void consumer3()
{
	while(1){
		P(full);
		P(mutex);
		buff[out] = 0;
		out = (out + 1) % N;
		printf("CONSUMER 3 \n Buff[0]: %d\t Buff[1]: %d\t Buff[2]: %d\t Buff[3]: %d\t Buff[4]: %d\n", buff[0], buff[1], buff[2], buff[3], buff[4]);
		sleep(1);		
		V(mutex);
		V(empty);
	}
	return;
}


int main()
{
	//initialize RunQ
	runQ = (struct queue*) malloc(sizeof(struct queue));
	initQueue(runQ);

	//initialize semaphores
	mutex = (struct Semaphore*) malloc(sizeof(struct Semaphore));
	full = (struct Semaphore*) malloc(sizeof(struct Semaphore));
	empty = (struct Semaphore*) malloc(sizeof(struct Semaphore));
	InitSem(full, 0);
	InitSem(empty, N);
	InitSem(mutex, 1);

	printf("\n**************KEY************** \nBuff value of 1 denotes produced \nBuff value of 0 denotes consumed \n");
	printf("Threads will start in 3 seconds \n");
	printf("*******************************\n");
	sleep(3);
	

	//Start threads for producers and consumers
	startThread(consumer1);
	startThread(consumer2);
	startThread(consumer3);
	startThread(producer1);
	startThread(producer2);

	run();
	return 0;
}


