#include<stdlib.h>
#include<stdio.h>


typedef struct _dir * DirPtr;
typedef struct _tracker * TrackerPtr;

typedef struct _dir {
	char* name;
	DirPtr child;
	DirPtr sibling;
} Dir;

typedef struct _tracker {
	DirPtr currentDir;
	TrackerPtr next;
} Tracker;

int runConsole(DirPtr, TrackerPtr);

DirPtr createDirectortElement(char*);
int makeDir(char*, TrackerPtr);
int changeDir(char*, TrackerPtr, DirPtr);
int exitConsole(TrackerPtr, DirPtr);
int listDir(TrackerPtr);
int freeDirs(DirPtr);

char* generatePositionString(TrackerPtr);
char* strrev(char*);

TrackerPtr createPosition(DirPtr);
int push(DirPtr, TrackerPtr);
int pop(TrackerPtr);
TrackerPtr initializeTracker(DirPtr dir);
