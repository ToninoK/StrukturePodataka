#ifndef HELPERS
#define HELPERS

#include<stdio.h>

typedef struct _element* Node;

typedef struct _element{
    int number;
    Node next;
} Element;


int getUnion(Node headOne, Node headTwo, Node unionList);
int getIntersection(Node headOne, Node headTwo, Node intersectionList);
int createElementsFromFile(char* filename, Node head);
Node createElement(int number);
FILE* safeOpen(char* filename, char* mode);
void printList(Node start);
int freeList(Node start);

#endif