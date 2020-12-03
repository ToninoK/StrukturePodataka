#include "helpers6.h"
#include<stdlib.h>

int generateRandom(int start, int end){
	return rand() % (start - end + 1) + start;
}

Node createElement(int number){
	Node new = (Node)malloc(sizeof(Element));
	if(new == NULL){
		printf("Memory allocation failed.");
		return new;
	}
	new->number = number;
	new->next = NULL;
	return new;
}

int pushStack(Node element, Node head){
	element->next = head->next;
	head->next = element;
	return 0;
}

int pushQueue(Node element, Node head){
	while(head->next!=NULL)
		head = head->next;
	head->next = element;
	return 0;
}


int pop(Node head){
	Node toDelete = head->next;
	if(toDelete == NULL)
		return 0;
	head->next = toDelete->next;
	free(toDelete);
}


void printList(Node start){
	while(start!=NULL){
		printf("%d\t", start->number);
		start = start->next;
	}
	printf("\n");
}


int freeList(Node head){
	while(head!=NULL){
		Node toDelete = head;
		head = head->next;
		free(toDelete);
	}
	return 0;
}
