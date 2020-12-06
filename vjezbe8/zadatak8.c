#include<stdlib.h>
#include "functionality.h"

int main(){
    DirPtr dir = (DirPtr)malloc(sizeof(Dir));
    dir->child = NULL;
    dir->sibling = NULL;
    dir->parent = NULL;
    dir->name = "~";
    TrackerPtr trackerHead = initializeTracker(dir);
    runConsole(dir, trackerHead);
    return 0;
}