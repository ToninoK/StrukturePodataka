#include<stdio.h>
#include<stdlib.h>

typedef struct _student* Node;
typedef struct _student** HashList;
typedef struct _hashTable* HashTablePtr;

typedef struct _student{
    int key;
    int mb;
    char* firstName;
    char* lastName;
    Node next;
}Student;

typedef struct _hashTable{
    HashList items;
    int numOfElements;
}HashTable;

Node createNewStudent(int, int, char*, char*);
int getHashKey(char*);
int storeStudent(Node, HashTablePtr);
FILE* safeOpen(char*, char*);
int insertWithSort(Node, Node);
int loadDataFromFile(char*, HashTablePtr);
int printHashTable(HashTablePtr);
int offerMBFetch(HashTablePtr);
int freeAll(HashTablePtr);

