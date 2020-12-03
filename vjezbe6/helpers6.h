#ifndef HELPERS
#define HELPERS

#include<stdio.h>

typedef struct _element* Node;
typedef struct _element{
	int number;
	Node next;
}Element;


int pushStack(Node, Node);
int pushQueue(Node, Node);
int pop(Node);
Node createElement(int);
int generateRandom(int, int);
void printList(Node);
int freeList(Node head);

#endif
