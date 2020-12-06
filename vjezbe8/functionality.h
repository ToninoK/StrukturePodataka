#include<stdlib.h>
#include<stdio.h>


typedef struct _dir * DirPtr;
typedef struct _tracker * TrackerPtr;

typedef struct _dir {
	char* name;
	DirPtr child;
	DirPtr sibling;
	DirPtr parent;
} Dir;

typedef struct _tracker {
	DirPtr currentDir;
	TrackerPtr next;
} Tracker;

int runConsole(DirPtr, TrackerPtr);

int makeDir(char*, DirPtr);
int changeDir(char*, TrackerPtr, DirPtr);
int exitConsole(TrackerPtr, DirPtr);
int listDir(DirPtr);
int freeDirs(DirPtr);
DirPtr findSearchedDir(char*, TrackerPtr, DirPtr, int);

char* generatePositionString(TrackerPtr);
char* getLastPathPart(char* argument);
char* getPathWithoutLast(char* argument);
int push(DirPtr, TrackerPtr);
int pop(TrackerPtr);
TrackerPtr initializeTracker(DirPtr);
DirPtr createDirectoryElement(char*);
TrackerPtr createPosition(DirPtr);
char* strrev(char*);

