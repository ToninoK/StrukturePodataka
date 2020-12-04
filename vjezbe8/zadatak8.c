#include<stdlib.h>
#include "helpers8.h"

int main(){
    DirPtr dir = (DirPtr)malloc(sizeof(Dir));
    dir->child = NULL;
    dir->sibling = NULL;
    dir->name = "C";
    TrackerPtr trackerHead = initializeTracker(dir);
    runConsole(dir, trackerHead);
    return 0;
}