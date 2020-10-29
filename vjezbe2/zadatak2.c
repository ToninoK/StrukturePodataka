#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _person* Node;
typedef struct _person{
	char firstName[100];
	char lastName[100];
	int birthYear;
	Node next;
}Person;

Node createPersonFromInput();
int pushFront(Node element, Node node);
int pushBack(Node element, Node node);
Node findElement(char* lastName, Node node);
int deleteElement(char* lastName, Node node);
int freeList(Node node);
int printList(Node node);

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
	while(strcmp(node->lastName, lastName) != 0)
		node = node->next;
	return node;
}

int deleteElement(char* lastName, Node node){
	Node toFree = findElement(lastName, node);
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
