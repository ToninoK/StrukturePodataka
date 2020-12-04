#include "helpers9.h"
#include<stdio.h>
#include<stdlib.h>

int main(){
    Node root = (Node)malloc(sizeof(Tree));
    root = NULL;
    root = push(6, root);
    root = push(3, root);
    root = push(7, root);
    root = push(9, root);
    printf("%d\n", root->number);
    
    printTree(root);
    printf("\n");
    deleteNode(7, root);
    printTree(root);
    printf("\n");
    Node found = findNode(9, root);
    printf("%d\n", found->number);
}