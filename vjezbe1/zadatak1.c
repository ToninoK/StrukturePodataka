#include <stdlib.h>
#include "helpers.h"
#define MAX_LINE_LENGTH 255


int main(){
    int numOfRows = countRowsInFile("./studenti.txt");
    if(!numOfRows){
        printf("File is empty");
        exit(0);
    }
    Student* students = loadStudentsFromFile("./studenti.txt", numOfRows);
    printStudentData(students, numOfRows);
    free(students);
    return 0;
}
