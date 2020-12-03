#ifndef HELPERS
#define HELPERS

#include<stdio.h>

typedef struct _element* Node;
typedef struct _element{
	float number;
	Node next;
}Element;

float calculateOperation(char, float, float);
int operateAndPush(char, Node);
float isFloat(char*);
FILE* safeOpen(char*, char*);
float calculatePostfix(char*, Node);
int push(Node, Node);
float pop(Node);
int operateAndPush(char c, Node head);
Node createElement(float);
void printList(Node);

#endif
