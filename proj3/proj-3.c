//Josh Barnes
//CSE330

#include "sem.h"
#include <stdio.h>

struct Semaphore *mutex = 0;
struct Semaphore *R_sem = 0;
struct Semaphore *W_sem = 0;
int wwc = 0, wc = 0, rwc =0, rc = 0;

void reader0()
{
	while(1)
	{

		printf("Reader 1 enter \n");
		sleep(1);
		P(mutex);
		if(wwc>0 || wc >0)
		{
			printf("Reader 1 in Scratch Pad \n");
			sleep(1);
			rwc++;
			//V(mutex);
			printf("Reader 1 leaving in Scratch Pad\n");
			sleep(1);
			P(R_sem);
			rwc--;
		}
		rc++;
		if(rwc > 0)
		{
			V(R_sem);
		}
		else
		{
			V(mutex);
		}

		P(mutex);
		printf("Reader 1 exit \n");
		sleep(1);
			rc--;
			if(rc == 0 && wwc > 0)
			{
				V(W_sem);
			}
			else
			{
				V(mutex);
			}
	}
}

void reader1()
{
	while(1)
	{
		printf("Reader 2 enter \n");
		sleep(1);
		P(mutex);
		if(wwc>0 || wc >0)
		{
			printf("Reader 2 in Scratch Pad\n");
			sleep(1);
			rwc++;
			V(mutex);
			printf("Reader 2 leaving Scratch Pad\n");
			sleep(1);
			P(R_sem);
			rwc--;
		}
		rc++;
		if(rwc > 0)
		{
			V(R_sem);
		}
		else
		{
			V(mutex);
		}

		P(mutex);
		printf("Reader 2 exit \n");
		sleep(1);
			rc--;
			if(rc == 0 && wwc > 0)
			{
				V(W_sem);
			}
			else
			{
				V(mutex);
			}
	}

}

void reader2()
{
	while(1)
	{
		printf("Reader 3 enter \n");
		sleep(1);
		P(mutex);
		if(wwc>0 || wc >0)
		{
			printf("Reader 3 in Scratch Pad\n");
			sleep(1);
			rwc++;
			V(mutex);
			printf("Reader 3 leaving Scratch Pad\n");
			sleep(1);
			P(R_sem);
			rwc--;
		}
		rc++;
		if(rwc > 0)
		{
			V(R_sem);
		}
		else
		{
			V(mutex);
		}

		P(mutex);
		printf("Reader 3 exit \n");
		sleep(1);
			rc--;
			if(rc == 0 && wwc > 0)
			{
				V(W_sem);
			}
			else
			{
				V(mutex);
			}
	}

}

void writer0()
{
	while(1)
	{
		printf("Writer 1 enter \n");
		sleep(1);
		P(mutex);
		if(rc > 0 || wc > 0)
		{
			printf("Writer 1 in Scratch Pad\n");
			sleep(1);
			wwc++;
			printf("Writer 1 leaving Scratch Pad\n");
			sleep(1);
			V(mutex);
			P(W_sem);
			wwc--;
		}
		wc++;
		V(mutex);

		P(mutex);
		printf("Writer 1 exit \n");
		sleep(1);
		wc--;
		if(rwc > 0)
		{
			V(R_sem);
		}
		else if(wwc > 0)
		{
			V(W_sem);
		}
	}

}

void writer1()
{
	while(1)
	{
		printf("Writer 2 enter \n");
		sleep(1);
		P(mutex);
		if(rc > 0 || wc > 0)
		{
			printf("Writer 2 in Scratch Pad\n");
			sleep(1);
			wwc++;
			printf("Writer 2 leaving Scratch Pad\n");
			sleep(1);
			V(mutex);
			P(W_sem);
			wwc--;
		}
		wc++;
		V(mutex);

		P(mutex);
		printf("Writer 2 exit \n");
		sleep(1);
		wc--;
		if(rwc > 0)
		{
			V(R_sem);
		}
		else if(wwc > 0)
		{
			V(W_sem);
		}
	}
}

int main()
{

	
	//initialize RunQ
	runQ = (struct queue*) malloc(sizeof(struct queue));
	initQueue(runQ);

	//initialize semaphores
	mutex = (struct Semaphore*) malloc(sizeof(struct Semaphore));
	R_sem = (struct Semaphore*) malloc(sizeof(struct Semaphore));
	W_sem = (struct Semaphore*) malloc(sizeof(struct Semaphore));
	InitSem(mutex, 1);
	InitSem(R_sem, 0);
	InitSem(W_sem, 1);

	startThread(reader0);
	startThread(reader1);
	startThread(reader2);
	startThread(writer0);
	startThread(writer1);

	run();
	return 0;

}
