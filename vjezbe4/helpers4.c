#include <stdio.h>
#include<stdlib.h>

#include "helpers4.h"


FILE* safeOpen(char * name, char* mode){
    FILE* fptr = fopen(name, mode);
    if(fptr==NULL){
        printf("File could not be opened.");
        exit(-1);
    }
    return fptr;
}


Node createElement(int exp, int fact){
    Node element = (Node)malloc(sizeof(Element));
    if(element == NULL){
        printf("Memory allocation error.");
        return element;
    }
    element -> exponent = exp;
    element -> factor = fact;
    element -> next = NULL;
    return element;
}


int fSortRead(Node start, char* filename){
    FILE* fptr = safeOpen(filename, "r");
    int exponent=0, factor=0;
    while (!feof(fptr)) {

        fscanf(fptr, "%d %d", &factor, &exponent);
        Node newElement = createElement(exponent, factor);
        if(newElement == NULL)
            exit(-1);

        Node previous = start;
        Node next = start->next;
        int inserted = 0;
        while(next != NULL){
            if(next->exponent < exponent){
                previous->next = newElement;
                newElement->next = next;
                inserted = 1;
            }
            previous = next;
            next = next->next;
        }
        if(!inserted){
            previous->next = newElement;
        }
    }
    fclose(fptr);
    return 0;
}


int sumPolynomials(Node startOne, Node startTwo, Node polynomialSum){
    while (startOne != NULL && startTwo !=NULL) {
        if (startOne->exponent == startTwo->exponent){
            polynomialSum->next = createElement(
                startOne->exponent,
                startOne->factor + startTwo->factor
            );
            polynomialSum = polynomialSum->next;
            startOne = startOne->next;
            startTwo = startTwo->next;
            continue;
        }
        if (startOne->exponent > startTwo->exponent){
            polynomialSum->next = startOne;
            polynomialSum = polynomialSum->next;
            startOne = startOne->next;
            continue;
        }
        if(startOne->exponent < startTwo->exponent){
            polynomialSum->next = startTwo;
            polynomialSum = polynomialSum->next;
            startTwo = startTwo->next;  
        }
    }
    return 0;
}


int insertAndSum(Node start, Node element){
    while(start!=NULL){
        if(start->exponent == element->exponent){
            start->factor += element->factor;
            return 0;
        }
        if(start->exponent > element->exponent){
            if(start->next == NULL){
                start->next = element;
                return 0;
            }
        }
        start = start->next;
    }
    return 0;
}


int productOfPolinomials(Node startOne, Node startTwo, Node polynomialProduct){
    while(startOne!=NULL){
        while(startTwo!=NULL){
            insertAndSum(
                polynomialProduct,
                createElement(
                    startOne->exponent + startTwo->exponent,
                    startOne->factor * startTwo->factor
                )
            );
            startTwo = startTwo->next;
        }
        startOne = startOne->next;
    }
    return 0;
}


void printList(Node start){
    while (start!=NULL) {
        if(start->exponent!=0)
            printf("%dx^%d", start->factor, start->exponent);
        else 
            printf("%d", start->factor);
        if(start->next&&start->next->factor > 0)
            printf("+");
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
