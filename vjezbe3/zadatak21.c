#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LINE_LENGTH 255

typedef struct _person* Node;
typedef struct _person{
	char firstName[100];
	char lastName[100];
	int birthYear;
	Node next;
}Person;


int pushFront(Node element, Node node);
int pushBack(Node element, Node node);
int insertBefore(Node element, Node target, Node head);
int insertAfter(Node element, Node target, Node head);
int deleteElement(char* lastName, Node node);

Node findElement(char* lastName, Node node);
int sortListByLastName(Node head);
int writeToFile(Node first, char* filename);
int readFromFile(Node head, char* filename);
int freeList(Node node);
void printList(Node node);

Node createPersonFromInput();
int countRowsInFile(FILE* fptr);
FILE* safeOpen(char* filename, char* mode);


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
