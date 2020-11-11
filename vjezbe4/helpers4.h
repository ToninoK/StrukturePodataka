#ifndef HELPERS
#define HELPERS

#include<stdio.h>

typedef struct _element* Node;

typedef struct _element{
    int exponent;
    int factor;
    Node next;
} Element;

int fSortRead(Node start, char* filename); 
Node sumElement(Node elOne, Node elTwo);
int sumPolynomials(Node startOne, Node startTwo, Node sumPolynomial);
int productOfPolynomials(Node startOne, Node startTwo, Node polynomialProduct);
int insertAndSum(Node start, Node element);
FILE* safeOpen(char* filename, char* mode);
void printList(Node start);
int freeList(Node start);

#endif