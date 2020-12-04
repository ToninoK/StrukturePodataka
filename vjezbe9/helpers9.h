#include<stdio.h>
#include<stdlib.h>

typedef struct _tree* Node;

typedef struct _tree{
    int number;
    Node left;
    Node right;
} Tree;

Node push(int number, Node start);
int printTree(Node start);
Node deleteNode(int number, Node start);
Node findNode(int number, Node start);
int freeTree(Node start);
Node createNewNode(int number);
Node findLowestOfSubtree(Node start);