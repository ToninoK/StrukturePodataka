#include "helpers10.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


FILE* safeOpen(char* filename, char* c){
	FILE* f = fopen(filename, c);
	if(f == NULL){
		printf("File could not be opened.");
		return NULL;
	}
	return f;
}


Node createNewNode(char* val){
    Node newNode = (Node)malloc(sizeof(Tree));
    if(newNode==NULL)
        return NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->member = (char*)malloc(sizeof(char)*strlen(val));
    strcpy(newNode->member, val);
    return newNode;
}


Node insertToTree(Node tree, Node root){
    if(root==NULL)
        return root;
    else if(root->left == NULL)
        root->left = tree;
    else if(root->right == NULL)
        root->right = tree;
    return root;
}


StackNode createNewStackNode(Node tree){
    StackNode newStackNode = (StackNode)malloc(sizeof(Stack));
    if(newStackNode==NULL){
        printf("Memory allocation error");
        return NULL;
    }
    newStackNode->treePointer = tree;
    newStackNode->next = NULL;
    return newStackNode;
}


int push(StackNode element, StackNode head){
	element->next = head->next;
	head->next = element;
	return 0;
}


Node pop(StackNode head){
	StackNode toDelete = head->next;
	if(toDelete == NULL)
		return 0;
	head->next = toDelete->next;
	Node tree = toDelete->treePointer;
	free(toDelete);
	return tree;
}


int isFloat(char* member){
	int isZero = strcmp(member, "0");
	float num = atof(member);
	if((num == 0 && isZero == 1) || num != 0)
		return 1;
	return 0;
}


Node readAndStorePostfix(char* filename, StackNode head){
    char buffer[100];
    FILE* f = safeOpen(filename, "r");
    fgets(buffer, 100, f);
    fclose(f);
    char* token;
    token = strtok(buffer, " ");
    while(token!=NULL){
        Node new = createNewNode(token);
        StackNode newStackNode = createNewStackNode(new);
        if(isFloat(token))
            push(newStackNode, head);
        else{
            new = insertToTree(pop(head), new);
            new = insertToTree(pop(head), new);
            push(newStackNode, head);
        }
        token = strtok(NULL, " ");
    }
    return pop(head);
}

int traverseAndWrite(FILE* f, Node tree, int previousIsOperation){
    if(tree==NULL)
        return 0;
    
    if(!isFloat(tree->member))
        fputc('(', f);

    traverseAndWrite(f, tree->left, previousIsOperation);

    fputs(tree->member, f);
    
    if(tree->right == NULL)
        return 0;
    
    traverseAndWrite(f, tree->right, previousIsOperation);
    fputc(')', f);

    return 0; 
}


int readPostfixWriteInfix(char* filename, StackNode head){
    Node tree = readAndStorePostfix(filename, head);
    char inputFile[20];
    scanf("%s", inputFile);
    FILE* f = safeOpen(inputFile, "w");
    fputc('\n', f);
    traverseAndWrite(f, tree, 1);
    freeTree(tree);
    fputc('\n', f);
    fclose(f);
}

int freeTree(Node tree){
    if(tree==NULL)
        return 0;
    freeTree(tree->left);
    freeTree(tree->right);
    free(tree);
}