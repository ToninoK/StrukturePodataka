#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "helpers.h"
#define MAX_LINE_LENGTH 255

int pushFront(Node element, Node start){
	element->next = start->next;
	start->next = element;
	return 0;
}

int insertBefore(Node element, Node target, Node start){
	while(target!=start->next)
		start=start->next;
	pushFront(element, start);
	return 0;
}

int pushBack(Node element, Node start){
	while(start->next != NULL)
		start = start->next;
	start->next = element;
	return 0;
}

int insertAfter(Node element, Node target, Node start){
	while(target != start)
		start=start->next;
	pushFront(element, start);
	return 0;
}


Node findElement(char* lastName, Node node){
	while(node!=NULL && strcmp(node->lastName, lastName) != 0)
		node = node->next;
	return node;
}

int deleteElement(char* lastName, Node head){
	Node toFree = findElement(lastName, head);
	if(toFree==NULL)
		return 1;
	while(head->next != toFree)
		head = head->next;
	head->next = toFree->next;
	if(toFree!=NULL)
		free(toFree);
	return 0;
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

void printList(Node node){
	while(node != NULL){
		printf("%s %s %d\n", node->firstName, node->lastName, node->birthYear);
		node = node->next;
	}
}


int sortListByLastName(Node head){
	if(head==NULL)
		return 1;
	Node ptr, prevPtr, temp, firstSorted=NULL;
	while(head->next != firstSorted){
		prevPtr = head;
		ptr = head->next;
		while (ptr->next != firstSorted) {
			if (strcmp(ptr->lastName, ptr->next->lastName) > 0) {
				temp = ptr->next;
				prevPtr->next = temp;
				ptr->next = temp->next;
				temp->next = ptr;
				ptr = temp;
			}
			prevPtr = ptr;
			ptr = ptr->next;
		}
		firstSorted = ptr;
	}
	return 0;
}


int readFromFile(Node head, char * filename){
	FILE* file = safeOpen(filename, "r");
	int rows = countRowsInFile(file);
	for(int i=0; i < rows; i++){
		Node person = (Node)malloc(sizeof(Person));
        fscanf(
            file,
            "%s %s %d\n",
            person->firstName, person->lastName, &person->birthYear
        );
		person->next = NULL;
		pushBack(person, head);
    }
	fclose(file);
	return 0;	
}


int writeToFile(Node node, char* filename){
	FILE* file = safeOpen(filename, "w");
	while(node != NULL){
		fprintf(file, "%s %s %d\n", node->firstName, node->lastName, node->birthYear);
		node = node->next;
	}
	fclose(file);
	return 0;
}


int countRowsInFile(FILE * fptr){
    int counter = 0;    
    char line[MAX_LINE_LENGTH];

    while(!feof(fptr)){
        fgets(line, MAX_LINE_LENGTH, fptr);
        counter++;
    }
	rewind(fptr);
    return --counter;
}


FILE* safeOpen(char * name, char* mode){
    FILE* fptr = fopen(name, mode);
    if(fptr==NULL){
        printf("File could not be opened.");
        exit(-1);
    }
    return fptr;
}


Node createPersonFromInput(){
	Node person = (Node)malloc(sizeof(Person));
	person->next = NULL;
	printf("Enter person data in format: [name] [surname] [birth year]\n");
	scanf("%s %s %d", person->firstName, person->lastName, &person->birthYear);
	return person;	
}
