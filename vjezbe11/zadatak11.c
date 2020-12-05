#include "helpers11.h"
#include<stdlib.h>

int main(){
    HashTablePtr table = (HashTablePtr) malloc(sizeof(HashTable));
    table->numOfElements = 11;
    table->items = (HashList)malloc(sizeof(Node)*table->numOfElements);
    loadDataFromFile("test.txt", table);
    printHashTable(table);
    offerMBFetch(table);
    freeAll(table);
    return 0;
}