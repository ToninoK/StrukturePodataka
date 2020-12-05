#include<stdio.h>
#include<stdlib.h>
#include "helpers10.h"

int main(){
    char filename[30];
    StackNode head = (StackNode) malloc(sizeof(Stack));
    head->next = NULL;
    head->treePointer = NULL;
    scanf("%s", filename);
    readPostfixWriteInfix(filename, head);
    return 0;
}