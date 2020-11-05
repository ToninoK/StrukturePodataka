#include<stdio.h>
#include<stdlib.h>
#include "helpers.h"

int main(){
	Node head = (Node )malloc(sizeof(Person));
	head->next = NULL;
	char search[100];

	pushFront(createPersonFromInput(), head);
	printf("\nList after entry:\n");
	printList(head->next);
	printf("\n\n");

	pushBack(createPersonFromInput(), head);
	printf("\nList after entry:\n");
	printList(head->next);

	printf("\n\nEnter the last name of the person you want to find:\n");
	scanf("%s", search);

	Node searchElement = findElement(search, head);
	if(searchElement!=NULL)
		printf(
			"\nFound person: %s %s %d\n\n",
			searchElement->firstName,
			searchElement->lastName,
			searchElement->birthYear
		);

	printf("\n\nEnter the last name of the person you want to delete:\n");
	scanf("%s", search);
	deleteElement(search, head);

	printf("\nList of people after the delete:\n");
	printList(head->next);
	printf("\n\n");

	freeList(head);
}
