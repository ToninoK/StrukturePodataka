#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"
#define MAX_LINE_LENGTH 255


int countRowsInFile(char * fileName){
    int counter = 0;    
    FILE* fptr = safeOpen(fileName);
    char line[MAX_LINE_LENGTH];

    while(!feof(fptr)){
        fgets(line, MAX_LINE_LENGTH, fptr);
        counter++;
    }

    fclose(fptr);
    return --counter;
}


Student* loadStudentsFromFile(char* fileName, int numOfStudents){
    Student* students = (Student* )malloc(sizeof(Student) * numOfStudents);

    FILE* fptr = safeOpen(fileName);

    for(int i=0; i < numOfStudents; i++){
        fscanf(
            fptr,
            "%s %s %d\n",
            students[i].firstName, students[i].lastName, &(students[i].score)
        );
    }
    fclose(fptr);
    return students;
}   


void printStudentData(Student* students, int numOfStudents){
    printf("Podatci o studentima:\n\n");
    int max = findMaxScore(students, numOfStudents);
    for(int i=0; i < numOfStudents; i++)
        printf(
            " Ime:%s \n Prezime:%s \n RelativniBodovi:%.2f \n\n",
            students[i].firstName,
            students[i].lastName,
            (float) students[i].score / max * 100
        );
}


int findMaxScore(Student* students, int numOfStudents){
    int max = 0;
    for(int i=0; i < numOfStudents; i++)
        if(students[i].score > max)
            max = students[i].score;
    return max;
}


FILE* safeOpen(char * name){
    FILE* fptr = fopen(name, "r");
    if(fptr==NULL){
        printf("File could not be opened.");
        exit(-1);
    }
    return fptr;
}
