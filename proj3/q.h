#ifndef Q_H
#define Q_H

#include <stdlib.h>
#include <unistd.h>
#include "tcb.h"


//create a queue struct
typedef struct queue {
	struct TCB_t *header;
} queue;

//forward declarations
void initQueue(struct queue*);
void addQueue(struct queue*, struct TCB_t*);
void rotateQ(struct queue*);
struct TCB_t* delQueue(struct queue*);
struct TCB_t* newItem();

//creates a empty queue, pointed to by the variable head
void initQueue(struct queue *head) {
	head->header = NULL;
	return;
}

//adds a queue item, pointed to by "item", to the queue pointed by the head
void addQueue(struct queue *head, struct TCB_t *item) {
	if (head->header != NULL) {
		if (head->header->next != NULL) {
			item->prev = head->header->prev;
			item->next = head->header;
			head->header->prev->next = item;
			head->header->prev = item;
		} else {
			head->header->next = item;
			head->header->prev = item;
			item->next = head->header;
			item->prev = head->header;
		}
	} else {
		head->header = item;
		item->prev = NULL;
		item->next = NULL;
	}

	return;
}

//moves the header pointer to the next element in the queue
void rotateQ(struct queue *head) {

	addQueue(head, delQueue(head));
	return;
}

//deletes an item from head and returns a pointer to the deleted item
struct TCB_t* delQueue(struct queue *head) {

	struct TCB_t *item = head->header;

	if (head->header != NULL) {
		if (head->header->next != NULL) {

			head->header->prev->next = head->header->next;
			head->header->next->prev = head->header->prev;
			head->header = head->header->next;
		} else {
			head->header = NULL;
		}
	}

	return item;
}

//returns a pointer to a new q-element
struct TCB_t* newItem() {
	// Allocate memory for new Queue element
	struct TCB_t *item = (struct TCB_t*) malloc(sizeof(struct TCB_t));

	return item;
}

#endif
