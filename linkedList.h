#include <stdlib.h>
#include <stdio.h>
//#include "vsftp.h"
//#include "rudp.h"

typedef struct node* Node;
struct node {
	void* data;
	Node next;
	Node prev;
};

void freeNode(Node node) {
	if (node == NULL) {
		return;
	}
	free(node);
}

/**
 * Private list type and structure
 * contains the head and tail of the list and the size
 */
struct linkedList {
	Node head;
	Node tail;
	int size;
};


struct linkedList * newList() {
	struct linkedList * list;
	list = (struct linkedList *) malloc(sizeof(struct linkedList));
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return list;
}

int listAdd(struct linkedList * list, void* data) {
	Node nod;
	nod = (Node) malloc(sizeof(struct node));
	if (nod == NULL) {
		return -1;
	}
	nod->data = data;
	if (list->head == NULL) {
		list->head = nod;
		list->tail = nod;
		nod->prev = NULL;
		nod->next = NULL;
		//	printf("Data inserted at Head %d\n",*(int*)list->head->data);
		//	printf("head:%p tail:%p\n",list->head,list->tail);
	} else {
		list->tail->next = nod;
		nod->prev = list->tail;
		nod->next = NULL;
		list->tail = nod;
		//	printf("head:%p tail:%p\n",list->head,list->tail);

		//	printf("Data inserted at Head %d\n",*(int*)list->head->data);
		//	printf("Data inserted at Tail %d\n",*(int*)list->tail->data);
	}

	//	printf("**********************head:%p tail:%p\n",list->head,list->tail);
	//	printf("Data found at Head %d\n",*(int*)list->head->data);
	//	printf("Data found at Tail %d\n",*(int*)list->tail->data);

	list->size += 1;
	return 1;//success
}

Node list_get(struct linkedList * list, int element) {
	if (element >= list->size || element < 0) {
		fprintf(stderr, "List element out of range: %d", element);
		return NULL;
	}
	Node search = list->head;
	int i;
	for (i = 0; i < element; i++) {
		search = search->next;
	}
	return search;
}

int listRemove(struct linkedList * list, int element) {
	if (element >= list->size || element < 0) {
		return -1; //error
	} else if (element == list->size - 1 && element == 0) {
		Node nod = list->head;
		freeNode(nod);
		list->size -= 1;
		list->head = NULL;
		list->tail = NULL;
		return 1;
	} else if (element == 0) {
		Node nod = list->head;
		list->head = nod->next;
		nod->next->prev = NULL;
		freeNode(nod);
		list->size -= 1;
		return 1;//success
	} else if (element == (list->size) - 1) {
		Node nod = list->tail;
		nod->prev->next = NULL;
		list->tail = list->tail->prev;
		freeNode(nod);
		list->size -= 1;
		return 1;//success
	} else {
		Node nod = list->head;
		int i;
		for (i = 0; i < element; i++) {
			nod = nod->next;
		}
		nod->next->prev = nod->prev;
		nod->prev->next = nod->next;
		freeNode(nod);
		list->size -= 1;
		return 1;//success
	}
}

/**
 * Returns the size of the list.
 */
int listSize(struct linkedList * list) {
	return list->size;
}

/**
 * Frees the list from memory by first removing all the nodes
 * and then free the list ptr.
 */
void listFree(struct linkedList * list) {
	int i;
	int init_size = listSize(list);
	for (i = 0; i < init_size; i++) {
		listRemove(list, 0);
	}
	freeNode(list->head);
	freeNode(list->tail);
	free(list);
}

Node popHead(struct linkedList* list) {
	Node head = list->head;
	list->size -= 1;
	list->head = head->next;
	if (list->head!=NULL) {
	list->head->prev = NULL;
	}
	//	listRemove(list,0);
	return head;
}

void printList(struct linkedList * list) {
	Node head;
	for (head = list->head; head != NULL; head = head->next) {
		printf("%d\n", *(int*) head->data);
	}
}



int containsNode(struct linkedList* list,void * data, int(*comparisionFunction)(void* data,Node node)){
		Node head;
		for (head = list->head; head != NULL; head = head->next) {
			if (comparisionFunction(data,head)) {
				return 1;
			}
		}
		return 0;
}

Node fetchNode(struct linkedList* list,void * data, int(*comparisionFunction)(void* data,Node node)){
		Node head;
		if (list==NULL) {
			return NULL;
		}
		for (head = list->head; head != NULL; head = head->next) {
			if (comparisionFunction(data,head)) {
				return head;
			}
		}
		return  NULL;
}

int fetchNodeArray(struct linkedList* list,void * data, int(*comparisionFunction)(void* data,Node node),struct node *** nodeArray){
		Node head;
		int count=0;
		for (head = list->head; head != NULL; head = head->next) {
			if (comparisionFunction(data,head)) {
				count++;
			}
		}

		if (count==0) {
			return -1;
		}

		*nodeArray = (struct node **)malloc(sizeof(struct node*)*count);
		int i = 0;

		for (head = list->head; head != NULL; head = head->next) {
					if (comparisionFunction(data,head)) {
						*nodeArray[i]=head;
						i++;
					}
				}

		return count;
}


