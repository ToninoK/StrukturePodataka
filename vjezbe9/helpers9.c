#include<stdio.h>
#include<stdlib.h>
#include "helpers9.h"

Node createNewNode(int number){
    Node newNode = (Node)malloc(sizeof(Tree));
    if(newNode==NULL)
        return NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->number = number;
    return newNode;
}

Node push(int number, Node start){
    if(start==NULL)
        return createNewNode(number);
    else if(number < start->number)
        start->left = push(number, start->left);
    else if(number > start->number)
        start->right = push(number, start->right);
    return start;
}

int printTree(Node start){
    if(start == NULL)
        return 1;
    printTree(start->left);
    printf("%d\t", start->number);
    printTree(start->right);
    return 0;
}


Node findLowestOfSubtree(Node start){
    if(start == NULL)
        return NULL;
    if(start->left != NULL)
        return findLowestOfSubtree(start->left);
    return start;
}


Node deleteNode(int number, Node start){
    Node lowest;
    if(start == NULL) return start;
    //Ako je trazeni broj manji od promatranog setamo u livo po stablu dalje
    if(number < start->number)
        start->left = deleteNode(number, start->left);
    //Ako je trazeni broj veci od promatranog setamo u desno po stablu dalje
    else if(number > start->number)
        start->right = deleteNode(number, start->right);
    //Ocito je trazeni broj jednak promatranom broju
    else{
        // Slucaj kad cvor koji zelimo obrisati ima dvoje djece
        if(start->left != NULL && start->right != NULL){
            // Trazimo minimum u desnoj grani
            lowest = findLowestOfSubtree(start->right);
            start->number = lowest->number;
            // Pozivamo ponovno funkciju te je ovaj put svedeno na slucaj jedne grane
            start->right = deleteNode(start->number, start->right);
        }
        else{
            lowest = start;
            // Slucaj kad promatramo leaf
            if(start->left==NULL) start = start->right;
            // Slucaj kad promatramo cvor s jednom granom
            else start = start->left;
            free(lowest);
        }
    }
    return start;
}


Node findNode(int number, Node start){
    if(start==NULL || start->number == number) return start;
    if(number < start->number)
        return findNode(number, start->left);
    return findNode(number, start->right);
}


int freeTree(Node start){
    if(start == NULL) return 0;
    freeTree(start->left);
    freeTree(start->right);
    free(start);
}