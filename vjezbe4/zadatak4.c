#include<stdio.h>
#include<stdlib.h>
#include "helpers4.h"

int main(){
    char p1[50], p2[50];
    scanf("%s", p1);
    scanf("%s", p2);

    Node headOne = (Node)malloc(sizeof(Element));
    Node headTwo = (Node)malloc(sizeof(Element));
    Node sum = (Node)malloc(sizeof(Element));
    Node product = (Node)malloc(sizeof(Element));
    fSortRead(headOne, p1);
    fSortRead(headTwo, p2);
    sumPolynomials(headOne->next, headTwo->next, sum);
    productOfPolynomials(headOne->next, headTwo->next, product);


    printList(headOne->next);
    freeList(headOne);

    printList(headTwo->next);
    freeList(headTwo);

    printList(sum->next);
    freeList(sum);

    printList(product->next);
    freeList(product);
    return 0;
}