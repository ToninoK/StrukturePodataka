#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "helpers6.h"

int main(){
	time_t t;
	srand((unsigned) time(&t));
	Node stack = (Node)malloc(sizeof(Element));
	Node queue = (Node)malloc(sizeof(Element));

///////////////////////Just testing///////////////////////////
	for(int i=0; i<5; i++){
		int random = generateRandom(10, 100);
		Node element = createElement(random);
		pushStack(element, stack);
		if(i%2==0)
			pop(stack);
	}
	for(int i=0; i<5; i++){
		int random = generateRandom(10, 100);
		Node element = createElement(random);
		pushQueue(element, queue);
		if(i%2==0)
			pop(queue);
	}
	printList(stack->next);
	printList(queue->next);
//////////////////////////////////////////////////////////////

	freeList(stack);
	freeList(queue);
	return 0;
}
