#include<stdlib.h>
#include<stdio.h>
#include "helpers11.h"
#include<string.h>


FILE* safeOpen(char* filename, char* c){
	FILE* f = fopen(filename, c);
	if(f == NULL){
		printf("File could not be opened.");
		return NULL;
	}
	return f;
}


Node createNewStudent(int key, int mb, char* firstName, char* lastName){
    Node student = (Node)malloc(sizeof(Student));
    if(student == NULL){
        printf("Memory allocation fail.");
        return NULL;
    }
    student->next = NULL;
    student->key = key;
    student->mb = mb;
    student->firstName = (char*)malloc(sizeof(char*)*strlen(firstName));
    student->lastName = (char*)malloc(sizeof(char*)*strlen(lastName));
    strcpy(student->firstName, firstName);
    strcpy(student->lastName, lastName);
    return student;
}

int getHashKey(char* lastName){
    int key = 0;
    int count = 0;
    // While sluzi za handleanje slucaja kad prezime ima na primjer 3 slova
    // Tada ce kruziti ispocetka dok ne zbroji 5 ascii kodova
    while(count != 5){
        for(int i = 0; i < strlen(lastName)-1; i++){
            key += lastName[i];
            count++;
            if(count == 5)
                break;
        }
    }
    return key;
}


int insertWithSort(Node new, Node head){
    Node previous = head;
    Node next = head->next;
    while(next != NULL){
        int byLastName = strcmp(next->lastName, new->lastName); 
        int byFirstName = strcmp(next->firstName, new->firstName); 
        if(byLastName > 0 || (byLastName == 0 && byLastName > 0)){
            previous->next = new;
            new->next = next;
        }
        previous = next;
        next = next->next;
    }
    return 0;
}


int storeStudent(Node student, HashTablePtr hashTable){
    HashList items = hashTable->items;
    int inserted = 0;
    int i=0;
    for(i = 0; i < hashTable->numOfElements; i++){
        if(items[i] == NULL)
            break;
        if(items[i]->next->key == student->key){
            inserted = 1;
            insertWithSort(student, items[i]);
            break;
        }
    }
    if(!inserted){
        Node head = (Node)malloc(sizeof(Student));
        head->next = student;
        items[i] = head;
    }
    return 0;
}


int loadDataFromFile(char* filename, HashTablePtr table){
    FILE* f = safeOpen(filename, "r");
    int mb;
    char firstName[64], lastName[64];
    char buffer[256];
    while(!feof(f)){
        fscanf(f, "%d %s %s\n", &mb, firstName, lastName);
        int hash = getHashKey(lastName);
        Node student = createNewStudent(hash, mb, firstName, lastName);
        storeStudent(student, table);
    }
    fclose(f);
    return 0;
}


int printHashTable(HashTablePtr table){
    printf("No.\t\tHash\t\tMB\t\tIme\t\tPrezime\n");
    for(int i = 0; i < table->numOfElements; i++)
        if(table->items[i]!=NULL){
            Node head = table->items[i];
            while(head->next!=NULL){
                printf(
                    "%d.\t\t%d\t\t%d\t\t%s\t\t%s\n",
                    i+1,
                    head->next->key,
                    head->next->mb,
                    head->next->firstName,
                    head->next->lastName
                );
                head = head->next;
            }
        }
            
    return 0;
}

int offerMBFetch(HashTablePtr table){
    while(1){
        char confirmation[32];
        char firstName[64], lastName[64];

        printf("Zelite li dohvatiti maticni broj studenta (y/n): ");
        scanf("%s", confirmation);

        if(strcmp("n", confirmation) == 0)
            break;

        else if(strcmp("y", confirmation) == 0){
            int found = 0;

            printf("Unesi ime i prezime ([ime] [prezime]): ");
            scanf("%s %s", firstName, lastName);

            for(int i = 0; i < table->numOfElements; i++)
                if(table->items[i]!=NULL){
                    Node head = table->items[i];
                    while(head->next!=NULL){
                        if(strcmp(firstName, head->next->firstName)==0 && strcmp(lastName, head->next->lastName)==0){
                            printf(
                                "%d.\t\t%d\t\t%d\t\t%s\t\t%s\n",
                                i+1,
                                head->next->key,
                                head->next->mb,
                                head->next->firstName,
                                head->next->lastName
                            );
                            found = 1;
                        }
                        head = head->next;
                    }
                }
            if(!found)
                printf("Osoba koju ste trazili ne postoji.\n");
        }
        
        else
            printf("Probaj opet\n");
    }
}


int freeAll(HashTablePtr table){
    for(int i = 0; i < table->numOfElements; i++)
        if(table->items[i]!=NULL){
            Node head = table->items[i];
            while(head!=NULL){
                Node toDelete = head;
                head = head->next;
                free(toDelete);
            }
        }
    free(table->items);
}