#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "helpers.h"

int pushFront(Node element, Node node){
	element->next = node->next;
	node->next = element;
	return 0;
}

int pushBack(Node element, Node node){
	while(node->next != NULL)
		node = node->next;
	node->next = element;
	return 0;
}

Node findElement(char* lastName, Node node){
	while(node!=NULL && strcmp(node->lastName, lastName) != 0)
		node = node->next;
	return node;
}

int deleteElement(char* lastName, Node node){
	Node toFree = findElement(lastName, node);
	if(toFree==NULL)
		return 1;
	while(node->next != toFree)
		node = node->next;
	node->next = toFree->next;
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

int printList(Node node){
	while(node != NULL){
		printf("%s %s %d\n", node->firstName, node->lastName, node->birthYear);
		node = node->next;
	}
	return 0;
}


Node createPersonFromInput(){
	Node person = (Node)malloc(sizeof(Person));
	person->next = NULL;
	printf("Enter person data in format: [name] [surname] [birth year]\n");
	scanf("%s %s %d", person->firstName, person->lastName, &person->birthYear);
	return person;	
}
