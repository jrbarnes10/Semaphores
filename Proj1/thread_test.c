//Josh Barnes
//Project 1
//CSE330


#include "thread.h"
#include <stdio.h>

//create global variable
int globalVar = 0;

void threadFunction1(void) {

	//create localVar variable
	int localVar = 1;

	while(1){
		printf("Thread 1:\n");
		printf("Global Variable: %d\tLocal Variable: %d\n", globalVar, localVar);	
		globalVar = globalVar + 1;
		localVar = localVar + 1;
		sleep(3);
		yield();
	}
	return;
}

void threadFunction2(void) {

	//create localVar variable
	int localVar = 2;

	while(1){
		printf("Thread 2: \n");
		printf("Global Variable: %d\tLocal Variable: %d\n", globalVar, localVar);	
		globalVar = globalVar + 1;
		localVar = localVar + 2;
		sleep(3);
		yield();
	}
	return;
}

void threadFunction3(void) {

	//create localVar variable
	int localVar = 3;

	while(1){
		printf("Thread 3 \n");
		printf("Global Variable: %d\tLocal Variable: %d\n", globalVar, localVar);
		globalVar = globalVar + 1;
		localVar += 3;
		sleep(3);
		yield();
	}

	return;
}

void threadFunction4(void) {

	//create localVar variable
	int localVar = 4;

	while(1){
		printf("Thread 4 \n");
		printf("Global Variable: %d\tLocal Variable: %d\n", globalVar, localVar);
		globalVar = globalVar + 1;
		localVar += 3;
		sleep(3);
		yield();
	}

	return;
}

int main() {

	//initialize RunQ
	runQ = (struct queue*) malloc(sizeof(struct queue));

	initQueue(runQ);

	startThread(threadFunction1);
	startThread(threadFunction2);
	startThread(threadFunction3);
	startThread(threadFunction4);
	run();

	return 0;
}
