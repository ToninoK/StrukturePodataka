#include "helpers8.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>


DirPtr createDirectoryElement(char* name){
	DirPtr newDir = (DirPtr)malloc(sizeof(Dir));
	if(newDir == NULL){
		printf("Directory could not be created");
		return NULL;
	}
	newDir->name = (char *)malloc(strlen(name) + 1);
	strcpy(newDir->name, name);
	newDir->child = NULL;
	newDir->sibling = NULL;
	return newDir;
}


TrackerPtr createPosition(DirPtr dir){
	TrackerPtr newPosition = (TrackerPtr)malloc(sizeof(Tracker));
	if(newPosition == NULL){
		printf("Error while changing directory");
		return NULL;
	}
	newPosition->currentDir = dir;
	newPosition->next = NULL;
	return newPosition;
}


TrackerPtr initializeTracker(DirPtr dir){
    TrackerPtr trackerHead = (TrackerPtr)malloc(sizeof(Tracker));
    trackerHead->next = (TrackerPtr)malloc(sizeof(Tracker));
    trackerHead->next->currentDir = dir;
    trackerHead->next->next = NULL;
	return trackerHead;
}


int push(DirPtr dir, TrackerPtr position){
	TrackerPtr newPosition = createPosition(dir);
	newPosition->next = position->next;
	position->next = newPosition;
	return 0;
}


int pop(TrackerPtr position){
	TrackerPtr toDelete = position->next;
	if(toDelete == NULL)
		return 0;
	position->next = toDelete->next;
	free(toDelete);
	return 0;
}


int makeDir(char* name, TrackerPtr position){
	DirPtr currentDir = position->next->currentDir;
	DirPtr existingChild = currentDir->child;
	DirPtr temp = existingChild;
	while(temp != NULL){
		if(temp->name == name){
			printf("Directory with same name already exists.");
			return 1;
		}
		temp = temp->sibling;
	}
	
	DirPtr newDir = createDirectoryElement(name);
	currentDir->child = newDir;
	
	if(existingChild != NULL)
		newDir->sibling = existingChild;
	
	return 0;
}


int changeDir(char* dirName, TrackerPtr position, DirPtr dir){
	DirPtr currentDir = position->next->currentDir;
	DirPtr searchLevel = currentDir->child;
	char* token = strtok(dirName, "/");
	if(strcmp(token, "..") == 0){
		while(token!=NULL){
			pop(position);
			token = strtok(NULL, "/");		
		}
		return 0;
	}
	while(token!=NULL){
		while(searchLevel!=NULL && strcmp(searchLevel->name, token))
			searchLevel = searchLevel->sibling;
		if(searchLevel==NULL){
			printf("Unknown path\n");
			return 1;
		}
		push(searchLevel, position);
		searchLevel = searchLevel->child;
		token = strtok(NULL, "/");
	}
	return 0;
}


int listDir(TrackerPtr position){
	DirPtr currentDir = position->currentDir->child;
	while(currentDir!=NULL){
		printf("%s\t", currentDir->name);
		currentDir = currentDir->sibling;
	}
	printf("\n");
	return 0;
}


int exitConsole(TrackerPtr position, DirPtr dir){
	while(position->next!=NULL)
		pop(position);
	freeDirs(dir);
	return 0;
}


int freeDirs(DirPtr dir){
	if(dir==NULL)
		return 0;
	freeDirs(dir->child);
	freeDirs(dir->sibling);
	free(dir);
	return 0;
}


//strrev ne postoji za linux, improvizacija
char* strrev(char* str){
      char *start, *end;
      if (!str || !*str)
            return str;

      for (start = str, end = str + (strlen(str) - 1); end > start; start++, end--){
            char temp;
			temp = *start;
			*start = *end;
            *end = temp;
      }
      return str;
}


char* generatePositionString(TrackerPtr position){
	char* positionString = (char* )malloc(sizeof(char)*101);
	strcpy(positionString, "/");
	while(position->next != NULL){
		char* temp = (char* )malloc(sizeof(char)*101);
		strcpy(temp, position->next->currentDir->name);
		strrev(temp);
		strcat(positionString, temp);
		strcat(positionString, "/");
		free(temp);
		position = position->next;
	}
	strrev(positionString);
	return positionString;
}


int runConsole(DirPtr dir, TrackerPtr position){
	char line[50];
	while(1){
		char* posString = generatePositionString(position);
		printf("#(sh)[%s]-> ", posString);

		char* command;
		char* argument;
		//gets ne postoji u linux paketima, samo fgets sa standardnim ulazom
		fgets(line, 50, stdin);
		command = strtok(line, " ");
		argument = strtok(NULL, " ");
		command = strtok(command, "\n");
		argument = strtok(argument, "\n");

		if(strcmp("mkdir", command)== 0)
			makeDir(argument, position);

		else if(strcmp("cd", command) == 0)
			changeDir(argument, position, dir);

		else if(strcmp("ls", command) == 0){
			int err = 0;
			// Dodati funkciju za pronalazak zeljenog direktorija a ne mijenjanje na njega
			// Tu dodanu funkciju takoder implementirati kod mkdir funkcije 
			if(argument != NULL)
				err = changeDir(argument, position, dir);
			if(!err)
				listDir(position->next);
		}

		else if(strcmp("exit", command) == 0){
			exitConsole(position, dir);
			return 0;
		}

		else
			printf("sh: command not found: %s\n", command);

		free(posString);
	}
}