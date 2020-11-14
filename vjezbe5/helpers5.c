#include <stdio.h>
#include<stdlib.h>

#include "helpers5.h"


int getUnion(Node headOne, Node headTwo, Node unionList){
    while (headOne != NULL || headTwo != NULL) {
        if (headTwo == NULL || headOne->number < headTwo->number) {
            unionList->next = createElement(headOne->number);
            unionList = unionList->next;
            headOne = headOne->next;
        }
        else if (headTwo == NULL || headOne->number > headTwo->number) {
            unionList->next = createElement(headTwo->number);
            unionList = unionList->next;
            headTwo = headTwo->next;
        }
        else if (headOne->number == headTwo->number) {
            unionList->next = createElement(headOne->number);
            unionList = unionList->next;
            headOne = headOne->next;
            headTwo = headTwo->next;
        }
    }
    return 0;
}

int getIntersection(Node headOne, Node headTwo, Node intersectionList){
    while (headOne != NULL || headTwo != NULL) {
        if(headOne==NULL || headTwo == NULL)
            break;
        else if (headOne->number < headTwo->number)
            headOne = headOne->next;
        else if (headOne->number > headTwo->number)
            headTwo = headTwo->next;
        else if (headOne->number == headTwo->number) {
            intersectionList->next = createElement(headOne->number);
            intersectionList = intersectionList->next;
            headOne = headOne->next;
            headTwo = headTwo->next;
        }
    }
    return 0;
}



int createElementsFromFile(char* filename, Node head){
    FILE* fptr = safeOpen(filename, "r");
    int number = 0;
    while (!feof(fptr)) {
        fscanf(fptr, " %d", &number);
        Node newElement = createElement(number);
        if(newElement==NULL)
            return -1;
        head->next = newElement;
        head = head->next;
    }
    fclose(fptr);
    return 0;
}


Node createElement(int number){
    Node new = (Node) malloc(sizeof(Element));
    if(new == NULL){
        printf("ERROR: Memory allocation (malloc) failed.");
        return new;
    }
    new->number = number;
    new->next = NULL;
    return new;
}



FILE* safeOpen(char* name, char* mode){
    FILE* fptr = fopen(name, mode);
    if(fptr==NULL){
        printf("WARNING: File could not be opened.");
        return NULL;
    }
    return fptr;
}


void printList(Node start){
    while (start!=NULL) {
        printf("%d", start->number);
        start = start->next;
    }
    printf("\n");
}


int freeList(Node head){
	Node toDelete = NULL;
	while(head->next != NULL){
		toDelete = head;
		head = head->next;
		free(toDelete);
	}
	return 0;
}