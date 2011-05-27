#ifndef LINKEDLIST_H
#define  LINKEDLIST_H

typedef struct node* Node;
struct node {
	void* data;
	Node next;
	Node prev;
};

struct linkedList {
	Node head;
	Node tail;
	int size;
};

struct linkedList * newList();
int containsNode(struct linkedList* list,void * data, int(*comparisionFunction)(void* data,Node node));
int listAdd(struct linkedList * list, void* data);

#endif
