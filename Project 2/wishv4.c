#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char **argv) {
	int childPid;
	int nbytes = 10;
	int parsed;
	
	char * cmdLine;
	char *info;
	
	char *command;
	
	command = (char *)malloc(nbytes+1);
	
	
	//interactive mode - always print out prompt and get the user entry
	if (argc > 1){
		while (1){
			puts("wish> ");
			getline(&command, &nbytes, stdin);
			
			//parse the user entry, returns 1 if successful
			char *p = strtok(command, " ");
			char *commandTok;
			
			int i = 0;
			while (p) {
				commandTok[i++] = p;
				p = strtok(NULL, " ");
			}
			
			//first token is the command
			info = commandTok[0];
			size_t commandLen = sizeof(commandTok)/sizeof(commandTok[0]);
	 
			if ( isBuiltInCommand(info) == 1){
				executeBuiltInCommand(info);
			} 
			else {		
				childPid = fork();
				if (childPid == 0){
					executeCommand(info); //calls execvp  
				
				} 
				else {
					waitpid (childPid);
				}
			}
		}
	}
	//batch mode
	if (argc == 1) {
		
	}
}

int addToPath(char str[]){
}

int isBuiltInCommand(char **str[]) {
	char *builtInCommands[] = {"exit", "cd", "path"};
	int len = sizeof(builtInCommands)/sizeof(builtInCommands[0]);
	
	* str = malloc(255);
	
	char arg[] = {0};
	strcpy(arg, str);
	
	for(int i = 0; i < len; ++i) {	
		if (!strcmp(arg, builtInCommands[i])) {
			fputs("It's here", stdout);
			
			return 1;
		}
		break;
	}
}

int executeBuiltInCommand(char str[]){
	
}

int executeCommand(char str[]){
	
}