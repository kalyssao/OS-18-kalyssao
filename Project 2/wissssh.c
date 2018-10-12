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

char path[900];
char commands[100];

char error_message[30] = "An error has occurred\n";
int commandLen = 0;

void addCommand(char *argv);
int checkBuiltIn(char *argv[]);
int executeOther();
void executeBuiltIn(int);
int batchMode(char *argv[]);
int interactiveMode();

void addCommand(char *argv) {
    int i = 0;
	int j = 0;
    commandLen = 0; //set command length to 0

    while(argv != NULL){
        commands[i] = argv[j];
        commandLen++;   //increment command length as there are values to add
		j++;
    }
    return; 
}

int checkBuiltIn(char *argv[]){
    if(!strcmp(argv[0], "exit")){
        puts("exiting...");
        return 10;
    }
    if(!strcmp(argv[0], "cd")){
        puts("changing directory...");
        return 9;
    }
    if(!strcmp(argv[0], "path")){
        puts("changing path...");
        return 8;
    }
    else {
        puts("Not a builtin command");
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
	
	//cd /cat/richChigga
	//check for exactly 2 commands
	//execute chdir(/cat/richChigga)
	//check to see the return value of chdir
	//if it is successful it means chigga got lit!!!
	//if not print thatlooooong error message and then exit
	//chigga ain't so lit anymore :-(
	//result /bin/cat
    if(a == 9) { //cd
        while(path[i] != NULL) { //raises type mismatch error
            strcpy(dir, path[i]);
            strcat(dir, "/");
            strcat(dir, commands[0]); //parameter count does not agree with previous definition
			//CHECK IF IT WORKSSSSSSSSSSS
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
		//could use an assignment, commands[i] = new_path
		//make others NULL
            path[0] = commands[i];// = strcpy(path, commands[1]);
        }
		//path = 0 /bin 1 /binbin NULL
		//command = path /stuff /path
		//commandLen = 3
        else {
            while(path[i] != NULL) {  //two for loops - first is
                for(j = 1; j < commandLen; ++j) { //at index 1, the first path to be copied
                    path[i] = commands[j]; //overwriting the contents of the path
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
            write(STDERR_FILENO, error_message, strlen(error_message));
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
int interactiveMode(){
    char *input = NULL;
    size_t len = 0;

    int i = 1;
    int retBI;
    int retEO;

    while(1) { // check for exit entry for while loop 
        fputs("wish> ", stdout);
        while(getline(&input, &len, stdin) != -1) { //while line

            //tokenize first item to commands array
            char *lastToken = strtok( input, " "); 
            //addCommand(lastToken);

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
            executeBuiltIn(retBI); //re
            continue;
        }
        else {
            retEO = executeOther(); //execute non builtin
            if(retEO == 0) {
                puts("Success!");
                continue;
            }
            else {
                break;
            }
        }
    }
}

//btchmode takes an array, attempts to open a file and
int batchMode(char *argv[]) {
    //int retCOM;
    int retBI;
    FILE *tokenFile;

    char str[1024];
    printf("Opening file named %s\n", argv[1]);
    tokenFile = fopen(argv[1], "r");
    
    // Check if the file doesn't exist
    if( tokenFile == NULL) {
            //bad batch file
            write(STDERR_FILENO, error_message, strlen(error_message)); 
            exit(1);
    }

        // If it exists, open it, read the line and tokenize it
    else {
        while( fgets( str, 1024, tokenFile) != NULL) {  //first line
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
            return 0; //return success
        }
    
    }
}

void main(int argc, char *argv[]) {
	//initialise path[0] to bin, path[1] = NULL
	
    int retB = ;//batch mode return
    int retI = ; //interactive mode return
    while(1) {
        if(argc == 1) {
            puts("entering interactive mode..");
            retI = interactiveMode();
    
            if(retI == 0) {
                puts("Interactive mode successful");
                continue;
            }
    
            else{
                break;
            }
        }
    
        if(argc == 2) {
            puts("entering batch mode...");
            retB = batchMode(argv[]);
    
            if(retB == 0 ) {
                puts("Success!");
                continue;
            }
            else {
                break;
            }
        }
    
        else {
            write(STDERR_FILENO, error_message, strlen(error_message));
            break; //return failure
        }
    }
}
