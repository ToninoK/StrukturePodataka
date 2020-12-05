#include<stdio.h>

typedef struct _tree* Node;
typedef struct _stack* StackNode;

typedef struct _tree{
    char* member;
    Node left;
    Node right;     
}Tree;

typedef struct _stack{
    Node treePointer;
    StackNode next;
}Stack;

FILE* safeOpen(char* filename, char* c);
int push(StackNode element, StackNode head);
Node pop(StackNode head);
int traverseAndWrite(FILE* f, Node tree, int previousIsOperation);
Node insertToTree(Node tree, Node root);
Node createNewNode(char* val);
Node readAndStorePostfix(char* filename, StackNode head);
StackNode createNewStackNode(Node tree);
int readPostfixWriteInfix(char* filename, StackNode head);
int isFloat(char* member);