//Kalyssa A. Owusu
//OS Lab 2
//Wisconsin Shell

// This project implements a shell program in C which operates in either batch or interactive mode, and executes commands - including three predefined builtin commands (cd, exit & path).
// Functions include: main: which determines which mode the shell should be run in, and calls either interactive or batch modes
// Other functions: a function for tokenizing strings
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//define global arrays for commands and the path - should they initially be empty?

char path[100];
char commands[100];

char error_message[30] = "An error has occurred\n";
int commandLen;

void addCommand(char *argv) {
	int i = 0;
	commandLen = 0; //set command length to 0

    while(argv != NULL){
        commands[i] = argv;
		commandLen++;	//increment command length as there are values to add
    }
    return; 
}

int checkBuiltIn(char *argv[]){
    if(!strcmp(argv[0], "exit")){
        return 10;
    }
    if(!strcmp(argv[0], "cd")){
        return 9;
    }
    if(!strcmp(argv[0], "path")){
        return 8;
    }
    else {
        return 7;
    }
}

void executeBuiltIn(int a) {
    int i = 0;
    int j;
    int retCH;
    
    char dir[100];
    
    if(a == 10) { //exit
        exit(0);
        
    }
    if(a == 9) { //cd
        while(path[i] != NULL) { //raises type mismatch error
            strcpy(dir, path[i]);
            strcat(dir, "/");
            strcat(dir, commands[0]); //parameter count does not agree with previous definition

            retCH = chdir(dir);

            if(retCH != 0) {
                //failure - incorrect path maybe?
                i++;
                continue;
            }
            else {
                //change was successful - break
                printf("Successfully changed directory to %s\n", dir);
            }
        }
        write(STDERR_FILENO, error_message, strlen(error_message));
        //printf("couldn't execute command %s\n", commands[0]);
    }
    //enquiring minds want to know! - commandLen var in which function?
    if(a == 8) {  //path - check if zero or more
        if(commandLen == 1) { //no arg - run nothing except builtin
            path[0] = NULL; //should the whole path be equated to NULL?
            puts("You can only run builtins");
        }
        if(commandLen == 2) { //one arg - overwrite current path
            strcpy(path, commands[1]);
        }
        else { // two args
            while(path[i] != NULL) {
                //path[i] = commands[j]; //overwriting the contents of the path
		for(j=1; j<commandLen; ++j){ //at index 1, the first path to be copied
                	strcpy(path[i], commands[j]);
			i++;
		}
	    	path[i] = NULL;
    	    }
	}
    }
}

//if not builtin - execute
int executeOther(){
    int i;
    int retEO;
    pid_t c_pid;

    c_pid = fork();
    while(path[i] != NULL) {
        if(access(path[i], X_OK) != 0) {
            //write error
        }
        else {
            retEO = execvp(&commands[0], commands); //warning pass argument two from incompatible type

            if(retEO == -1) {
                i++;
                continue;
                
            }

            else {
                return 0; //successful execution
            }
        }
    }
    write(STDERR_FILENO, error_message, strlen(error_message));
    //printf("couldn't execute command %s\n", commands[0]);
    return 1;
}

//one argument means interactive mode
void interactiveMode(){
    char *input = NULL;
    size_t len = 0;

    int i = 1;
    int retBI;

    while(1) {
        fputs("wish> ", stdout);
        while(getline(&input, &len, stdin) != -1) { //while line

            //tokenize first item to commands array
			char *lastToken = strtok( input, " "); 
            addCommand(lastToken);

			//while there are more words to tokenize
			while( lastToken != NULL) {
				addCommand(lastToken); //add command to command array
				lastToken = strtok( NULL, " "); //next token - arguments
				i++;
			}
        }
		printf("command is %s\n", commands[0]);
        retBI = checkBuiltIn(commands[0]);
        if( retBI != 7){
            executeBuiltIn(retBI);
            continue;
        }
        else {
            executeOther(); //execute non builtin
        }
    }
}

//more than one argument means batch mode
void batchMode(char *argv[]) {
    //int retCOM;
	int retBI;
    FILE *tokenFile;

    char str[1024];
	tokenFile = fopen(argv[1], "r");
    
	// Check if the file doesn't exist
	if( tokenFile == NULL) {
		//bad batch file
		write(STDERR_FILENO, error_message, strlen(error_message)); 
		exit(1);
	}

	// If it exists, open it, read the line and tokenize it
	else {
		while( fgets( str, 1024, tokenFile) != NULL) {	//first line
			char *lastToken = strtok( str, " "); 

			//while there are words to tokenize
			while( lastToken != NULL) {
				addCommand(lastToken); //add command to command array
				lastToken = strtok( NULL, " "); //next token - arguments
			}

			// end of line - check first command for builtin
			retBI = checkBuiltIn(commands[0]);

			if( retBI != 7) {
            	executeBuiltIn(retBI);
            	continue;
        	}

        	else {
            	executeOther(); //execute non builtin
        	}

			commandLen = 0;
		}
    
    }
}

int main(int argc, char *argv[]) {
	if(argc == 1) {
		interactiveMode();
		return 0; //return success - make interactive return a value and check?
	}
	if(argc == 2) {
		batchMode(argv);
		return 0;
	}
	else {
		write(STDERR_FILENO, error_message, strlen(error_message));
		return 1; //return failure
	}
}
