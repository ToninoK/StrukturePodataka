#ifndef HELPERS
#define HELPERS

#include<stdio.h>

typedef struct _person* Node;
typedef struct _person{
	char firstName[100];
	char lastName[100];
	int birthYear;
	Node next;
}Person;


int pushFront(Node element, Node node);
int pushBack(Node element, Node node);
int insertBefore(Node element, Node target, Node head);
int insertAfter(Node element, Node target, Node head);
int deleteElement(char* lastName, Node node);

Node findElement(char* lastName, Node node);
int sortListByLastName(Node head);
int writeToFile(Node first, char* filename);
int readFromFile(Node head, char* filename);
int freeList(Node node);
void printList(Node node);

Node createPersonFromInput();
int countRowsInFile(FILE* fptr);
FILE* safeOpen(char* filename, char* mode);

#endif
