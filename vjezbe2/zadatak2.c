#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _person{
	char firstName[100];
	char lastName[100];
	int birthYear;
	struct _person* next;
}Person;

Person* createPersonFromInput();
void pushFront(Person* element, Person* node);
void pushBack(Person* element, Person* node);
Person* findElement(char* lastName, Person* node);
void deleteElement(char* lastName, Person* node);
void freeList(Person* node);
void printList(Person* node);

int main(){
	Person* head = (Person* )malloc(sizeof(Person));
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

	Person* searchElement = findElement(search, head);
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

void pushFront(Person* element, Person* node){
	element->next = node->next;
	node->next = element;
}

void pushBack(Person* element, Person* node){
	while(node->next != NULL)
		node = node->next;
	node->next = element;
}

Person* findElement(char* lastName, Person* node){
	while(strcmp(node->lastName, lastName) != 0)
		node = node->next;
	return node;
}

void deleteElement(char* lastName, Person* node){
	Person* toFree = findElement(lastName, node);
	while(node->next != toFree)
		node = node->next;
	node->next = toFree->next;
	free(toFree);
}

void freeList(Person* head){
	Person* toDelete = NULL;
	while(head->next != NULL){
		toDelete = head;
		head = head->next;
		free(toDelete);
	}
}

void printList(Person* node){
	while(node != NULL){
		printf("%s %s %d\n", node->firstName, node->lastName, node->birthYear);
		node = node->next;
	}
}


Person* createPersonFromInput(){
	Person* person = (Person* )malloc(sizeof(Person));
	person->next = NULL;
	printf("Enter person data in format: [name] [surname] [birth year]\n");
	scanf("%s %s %d", person->firstName, person->lastName, &person->birthYear);
	return person;	
}
