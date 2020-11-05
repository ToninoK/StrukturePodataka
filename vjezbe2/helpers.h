#ifndef HELPERS
#define HELPERS

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

#endif