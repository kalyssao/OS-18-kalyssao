//Kalyssa A. Owusu
//OS Lab 2
//Wisconsin Shell

// This project implements a shell program in C which operates in either batch or interactive mode, and executes commands - including three predefined builtin commands (cd, exit & path).
// Functions include: main: which determines which mode the shell should be run in, and calls either interactive or batch modes
// Other functions: a function for tokenizing strings
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <process.h>

//define global arrays for commands and the path - should they initially be empty?

char path[100];
char commands[100];

char error_message[30] = "An error has occurred\n";

int commandLen;

void addCommands(char *argv[]){
    int i;
    while(argv[i] != NULL){
        commandLen = 0;
   
        commands[0] = argv[i];
        commandLen++;

    }
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
    int j = 0;
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
            fputs("You can only run builtins");
        }
        if(commandLen == 2) { //one arg - overwrite current path
            while(path[i] commands[1];){

            }
            
        }
        else { //
            while(path[i] != NULL) {
                //path[i] = commands[j]; //overwriting the contents of the 
                strncpy(path[i], NULL);
                i++;
            path[i] = NULL;
    }
}

int executeOther(){
    int i;
    int retEO;
    pid_t c_pid;

    c_pid = fork();
    while(path[i] != NULL) {
        if(access(path[i], X_OK)) != 0) {
            //write error
        }
        else {
            retEO = execvp(commands[0], commands);

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

void interactiveMode(){
    char *input = NULL;
    size_t len = 0;
    ssize_t read;

    int i = 0;
    int retBI;
    
    while(1) {
        fputs("wish> ");
        while(getline(&input, &len, stdin) != -1) {
            //while line is readable, tokenize contents to commands array
            commands[i] = tokenize(&input);
            i++;
        }
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

void batchMode(int argc, char *argv[]) {
    if(argc > 1) { //more than one argument means batch mode
        //read argv array into commands array
}
