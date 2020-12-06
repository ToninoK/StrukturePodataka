#include "functionality.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#define GREEN "\x1b[92m"
#define RED "\x1b[31m"
#define MAGENTA "\x1b[35m"
#define WHITE "\x1b[37m"
#define BLACK "\x1b[30m"
#define CYAN "\x1b[36m" 


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


TrackerPtr initializeTracker(DirPtr dir){
    TrackerPtr trackerHead = (TrackerPtr)malloc(sizeof(Tracker));
    trackerHead->next = (TrackerPtr)malloc(sizeof(Tracker));
    trackerHead->next->currentDir = dir;
    trackerHead->next->next = NULL;
	return trackerHead;
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


int push(DirPtr dir, TrackerPtr position){
	TrackerPtr newPosition = createPosition(dir);
	newPosition->next = position->next;
	position->next = newPosition;
	return 0;
}


int pop(TrackerPtr position){
	if(position->next->next == NULL)
		return 0;
	TrackerPtr toDelete = position->next;
	if(toDelete == NULL)
		return 0;
	position->next = toDelete->next;
	free(toDelete);
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
	strcpy(positionString, "");
	while(position->next != NULL){
		char* temp = (char* )malloc(sizeof(char)*101);
		strcpy(temp, position->next->currentDir->name);
		strrev(temp);
		strcat(positionString, "/");
		strcat(positionString, temp);
		free(temp);
		position = position->next;
	}
	strrev(positionString);
	return positionString;
}


char* getLastPathPart(char* argument){
	char* tokenFirst = strtok(argument, "/");
	char* tokenSecond = strtok(NULL, "/");
	while(tokenFirst != NULL){
		if(tokenSecond == NULL)
			return tokenFirst;
		if(tokenSecond!=NULL)
				strcpy(tokenFirst, tokenSecond);
			else
				break;
		tokenSecond = strtok(NULL, "/");
	}
	return tokenFirst;
}


char* getPathWithoutLast(char* argument){
	char* tokenFirst = strtok(argument, "/");
	char* tokenSecond = strtok(NULL, "/");
	if(tokenSecond == NULL)
		return NULL;
	
	char* newPath = (char*) malloc(sizeof(char)*101);
	strcpy(newPath, tokenFirst);
	strcat(newPath, "/");

	while(tokenFirst != NULL){
		strcpy(tokenFirst, tokenSecond);
		tokenSecond = strtok(NULL, "/");
		if(tokenSecond == NULL)
			break;
		
		strcat(newPath, tokenFirst);
		strcat(newPath, "/");
	}
	return newPath;
}


int makeDir(char* name, DirPtr currentDir){
	DirPtr existingChild = currentDir->child;
	DirPtr temp = existingChild;
	while(temp != NULL){
		if(strcmp(temp->name, name) == 0){
			printf("Directory with same name already exists.");
			return 1;
		}
		temp = temp->sibling;
	}
	
	DirPtr newDir = createDirectoryElement(name);
	currentDir->child = newDir;
	newDir->parent = currentDir;
	if(existingChild != NULL)
		newDir->sibling = existingChild;
	
	return 0;
}


int changeDir(char* dirName, TrackerPtr position, DirPtr dir){
	DirPtr currentDir = position->next->currentDir;
	DirPtr searchLevel = currentDir->child;
	char* token = strtok(dirName, "/");
	while(token!=NULL){
		if(strcmp(token, "..") == 0){
			pop(position);
			searchLevel = position->next->currentDir->child;
			token = strtok(NULL, "/");
			continue;
		}
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


int listDir(DirPtr currentDir){
	if(currentDir == NULL){
		printf("\n");
		return 0;
	}
	currentDir = currentDir->child;
	while(currentDir!=NULL){
		printf(MAGENTA "%s\t", currentDir->name);
		currentDir = currentDir->sibling;
	}
	printf("\n");
	return 0;
}


int exitConsole(TrackerPtr position, DirPtr dir){
	while(position!=NULL){
		TrackerPtr toDelete = position;
		position = position->next;
		free(toDelete);
	}
	freeDirs(dir);
	return 0;
}


DirPtr findSearchedDir(char* dirName, TrackerPtr position, DirPtr head, int withoutLast){
	DirPtr currentDir = position->next->currentDir;
	DirPtr searchLevel = currentDir->child;
	char* token = strtok(dirName, "/");
	while(token!=NULL){
		if(strcmp(token, "..") == 0){
			currentDir = currentDir->parent;
			searchLevel = currentDir->child;
			token = strtok(NULL, "/");
			continue;
		}
		while(searchLevel!=NULL && strcmp(searchLevel->name, token))
			searchLevel = searchLevel->sibling;

		if(searchLevel==NULL){
			printf("Unknown path\n");
			return NULL;
		}
		currentDir = searchLevel;
		searchLevel = searchLevel->child;
		token = strtok(NULL, "/");
	}
	return currentDir;
}


int runConsole(DirPtr dir, TrackerPtr position){
	char line[50];
	printf("Type help for commands\n");
	while(1){
		char* posString = generatePositionString(position);
		printf(GREEN "-> " CYAN "%s  " WHITE, posString);

		char* command;
		char* argument;
		//gets ne postoji u linux paketima, samo fgets sa standardnim ulazom
		fgets(line, 50, stdin);
		command = strtok(line, " ");
		argument = strtok(NULL, " ");
		command = strtok(command, "\n");
		argument = strtok(argument, "\n");

		if(strcmp("mkdir", command)== 0){
			if(argument == NULL)
				continue;
			char* argCpy = (char*)malloc(sizeof(char)*strlen(argument));
			strcpy(argCpy, argument);
			argument = getPathWithoutLast(argument);

			DirPtr	wanted = findSearchedDir(argument, position, dir, 1);
			free(argument);

			argument = getLastPathPart(argCpy);

			if(wanted==NULL)
				continue;
			makeDir(argument, wanted);
			free(argCpy);
		}

		else if(strcmp("cd", command) == 0){
			if(argument == NULL)
				while(strcmp(position->next->currentDir->name, "C") != 0)
					pop(position);
			else
				changeDir(argument, position, dir);
		}

		else if(strcmp("ls", command) == 0){
			DirPtr wanted = position->next->currentDir;
			if(argument != NULL)
				wanted = findSearchedDir(argument, position, dir, 0);
			listDir(wanted);
		}

		else if(strcmp("clear", command) == 0)
			system("clear");

		else if(strcmp("help", command) == 0){
			printf("\nThis emulation uses linux standard commands:\n");
			printf("mkdir [path]/[name]- Creates folder at given path with given name\n");
			printf("cd [path] - changes directory to the one given in path\n");
			printf("ls [path] - lists contents of directory given in the path\n");
			printf("clear - clears console screen\n");
			printf("help - writes this message :)\n\n");
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
