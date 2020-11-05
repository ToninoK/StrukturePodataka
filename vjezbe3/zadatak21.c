#include<stdio.h>
#include<stdlib.h>
#include "helpers.h"
#define MAX_LINE_LENGTH 255


int main(){
	Node head = (Node )malloc(sizeof(Person));
	head->next = NULL;
	char search[100], filename[100], newFilename[100];
	printf("Enter filename: ");
	scanf("%s", filename);

	readFromFile(head, filename);
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
		printf("\n\n");
		Node person1 = createPersonFromInput();
		Node person2 = createPersonFromInput();
		insertAfter(person1, searchElement, head);
		insertBefore(person2, searchElement, head);

	printf("\n\nEnter the last name of the person you want to delete:\n");
	scanf("%s", search);
	deleteElement(search, head);

	printf("\nList of people after the delete:\n");
	printList(head->next);
	printf("\n\n");

	sortListByLastName(head);
	printf("List of people after sorting\n");
	printList(head->next);
	printf("\n\n");

	printf("Enter name of file you want to write to: ");
	scanf("%s", newFilename);
	writeToFile(head->next, newFilename);

	freeList(head);
}
