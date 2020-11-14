#include<stdio.h>
#include <stdlib.h>

#include "helpers5.h"



int main(){

    Node headOne = (Node) malloc(sizeof(Element));
    Node headTwo = (Node) malloc(sizeof(Element));
    Node unionList = (Node) malloc(sizeof(Element));
    Node intersection = (Node) malloc(sizeof(Element));
    
    char a[20], b[20];
    scanf("%s", a);
    scanf("%s", b);

    createElementsFromFile(a, headOne);
    createElementsFromFile(b, headTwo);
    printList(headOne->next);
    printList(headTwo->next);
    
    getIntersection(headOne->next, headTwo->next, intersection);
    getUnion(headOne->next, headTwo->next, unionList);
    printList(intersection->next);
    printList(unionList->next);

    freeList(headOne);
    freeList(headTwo);
    freeList(intersection);
    freeList(unionList);

    return 0;
}