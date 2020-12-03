#include<stdio.h>
#include<stdlib.h>
#include "helpers7.h"

int main(){
	Node stackHead = (Node)malloc(sizeof(Element));
	float res = calculatePostfix("./test.txt", stackHead);
	printf("%.2f\n", res);
	free(stackHead);
	return 0;
}
