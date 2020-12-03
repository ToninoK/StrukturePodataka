#include "helpers7.h"
#include<string.h>
#include<stdlib.h>


FILE* safeOpen(char* filename, char* c){
	FILE* f = fopen(filename, c);
	if(f == NULL){
		printf("File could not be opened.");
		return NULL;
	}
	return f;
}


Node createElement(float number){
	Node new = (Node)malloc(sizeof(Element));
	if(new == NULL){
		printf("Memory allocation failed.");
		return new;
	}
	new->number = number;
	new->next = NULL;
	return new;
}

int push(Node element, Node head){
	element->next = head->next;
	head->next = element;
	return 0;
}


float pop(Node head){
	Node toDelete = head->next;
	if(toDelete == NULL)
		return 0;
	head->next = toDelete->next;
	float num = toDelete->number;
	free(toDelete);
	return num;
}


void printList(Node start){
	while(start!=NULL){
		printf("%d\t", start->number);
		start = start->next;
	}
	printf("\n");
}


int operateAndPush(char c, Node head){
	float a = pop(head);
	float b = pop(head);
	float result = calculateOperation(c, a, b);
	Node new = createElement(result);
	push(new, head);
	return 0;
}


float calculateOperation(char c, float a, float b){
	switch (c){
		case '+':
			return a+b;
		case '-':
			return a-b;
		case '*':
			return a*b;
		case '/':
			return a/b;
		default:
			return 0;
	}
}


float isFloat(char* member){
	int isZero = strcmp(member, "0");
	float num = atof(member);
	if((num == 0 && isZero == 1) || num != 0)
		return 1;
	return 0;
}


float calculatePostfix(char* filename, Node head){
	FILE* f = safeOpen(filename, "r");
	char postfix[100];
	fgets(postfix, 100, f);
	
	char* token;
	token = strtok(postfix, " ");
	
	while(token!=NULL){
		if(isFloat(token)){
			Node new = createElement(atof(token));
			push(new, head);
		}
		else
			operateAndPush(token[0], head);
		token = strtok(NULL, " ");
	}
	fclose(f);
	return pop(head);
}


