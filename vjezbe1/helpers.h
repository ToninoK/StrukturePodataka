#ifndef HELPERS
#define HELPERS

#include <stdio.h>

typedef struct _student{
    char firstName[30];
    char lastName[30];
    int score;
} Student;

int countRowsInFile(char*);
Student* loadStudentsFromFile(char*, int);
FILE* safeOpen(char*);
void printStudentData(Student*, int);
int findMaxScore(Student*, int);
#endif