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
#include <sys/wait.h>
#include <sys/types.h>

//define global arrays for commands and the path - should they initially be empty?

char path[900] = "/bin";
char *commands[900];

char error_message[30] = "An error has occurred\n";
int commandLen = 0;

int addCommand(char *argv);
int addCommands(char *argv[], int tokenLen);
int checkBuiltIn(char argv[]);
int executeOther();
void executeBuiltIn(int);
int batchMode(char *argv[]);
int interactiveMode();

int addCommands(char *argv[], int tokenLen) {
        int j = 0;
        for (int i = 0; i < tokenLen; ++i) {
                commands[j] = argv[i];
                j++;
        }
        commandLen = tokenLen;
        return 0; //return success
}

int addCommand(char *argv) { //adds a single command
        //printf("Added command %s to the array\n", argv);
        //return;
    //int i = 0;
        //int j = 0;
    commandLen = 0; //set command length to 0
    commands[0] = argv;
        printf("Successfully added command %s\n", commands[0]);
    commandLen++;   //increment command length as there are values to add
        
    return 0; //return success
}

int checkBuiltIn(char argv[]){
    if(!strcmp(&argv[0], "exit")){
        return 10;
    }
    if(!strcmp(&argv[0], "cd")){
        return 9;
    }
    if(!strcmp(&argv[0], "path")){
        puts("changing path...");
        return 8;
    }
    else {
        puts("Not a builtin command");
        return 7;
    }
}

void executeBuiltIn(int a) {
    FILE *fp;
    int i = 1;
    //int j;
    int retCH;
    printf("command length is %d\n", commandLen);
    //char dir[100];
    
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
        if(commandLen == 2) {
            //while(*path[i] != NULL) {
            retCH = chdir(commands[1]);
            /*strcpy(dir, path[i]);
            strcat(dir, "/");
            strcat(dir, commands[0]); //parameter count does not agree with previous definition
                        //CHECK IF IT WORKSSSSSSSSSSS*/
            //retCH = chdir(dir);

            if(retCH != 0) {
                //failure - incorrect path maybe?
                //i++;
                //continue;
                write(STDERR_FILENO, error_message, strlen(error_message));
                exit(1);
            }
            else {
                //change was successful - break
                printf("Successfully changed directory to %s\n", commands[1]);
                return;
            }
        }
        //more or less than 1 parameter
        write(STDERR_FILENO, error_message, strlen(error_message));
        return;
    }

    if(a == 8) {
        if(commandLen == 2) { //no arg - run nothing except builtin
            printf("Attention! You can only run builtins now.\n", stdout);
            fp = fopen("filepath.txt", w); //opens path file and empties it
        }
  
        else { //more than one argument of path
            fp = fopen("filenames.txt", w); //opens, deletes content and overwrites file
            while(commands[i] != '\0') {
                fprintf(fp, "%s ", commands[i]); // write path arguments into text file
            }
            return fp;
        }
    }
}

//if not builtin - execute
int executeOther() {
    int i = 0;
    int retEO;
    printf("executing other command %s with length %d\n", commands[0], commandLen);
    pid_t c_pid;

    c_pid = fork();

    FILE
    
    if(c_pid == 0) {
                while(path[i] != '\0') {
                        if(access(&path[i], X_OK) != 0) { //path is legit
                                    i++;
                                        continue;               
                        }
                        else {
                                retEO = execvp(commands[0], commands); //execvp given command
                                
                                if(retEO == -1) {
                                        puts("there was a problem..");      
                                }

                                else {
                                        puts("success");
                                        return 0; //successful execution
                                }
                        }       
                }
        }
        else {
                wait(NULL);
                return 1;
        }
        // write(STDERR_FILENO, error_message, strlen(error_message));
    return 1;
}

//one argument means interactive mode
int interactiveMode() {
    char *input = NULL;
    size_t len = 0;
        char *tokenArray[1024];

        int k = 0;
    int retBI;
    int retEO;
        int retAC;
        int tokenLen;

    while(1) { // check for exit entry for while loop 
        fputs("wish> ", stdout);
        while(getline(&input, &len, stdin) != -1) { //while line
                char* p = strchr(input,'\n');
                        if (p) {
                                *p = '\0';
                                        //tokenize first item to commands array
                        char *lastToken = strtok( input, " "); 
                                        tokenLen++;

                    //while there are more words to tokenize
                    while( lastToken != NULL ) {
                                                tokenArray[k] = lastToken;
                                                k++;
                                                tokenLen++;
                                                lastToken = strtok( NULL, " "); //rest of the arguments
                                                
                                        }
                        /* addCommand(lastToken); //add command to command array*/
                                        //after tokenizing line, add to commands array
                                        retAC = addCommands(tokenArray, tokenLen);

                                        if(retAC != 0) {
                                                write(STDERR_FILENO, error_message, strlen(error_message));
                                                break;
                                        }
                                        else {
                                                printf("command is %s\n", commands[0]);
                                        retBI = checkBuiltIn(commands[0]);

                                        if( retBI != 7){
                                        executeBuiltIn(retBI); //execute builtin depending on return value
                                        //continue;
                                        }

                                                else {
                                                        puts("executing other..\n");
                                                        retEO = executeOther(); //execute non builtin
                                                        if(retEO == 0) {
                                                                puts("Success!");
                                                                return 0;
                                                        }
                                                        else {
                                                                return 1;
                                                        }
                                                }
                                }
                                }
                                else { //eof error      
                                        exit(0);
                                        //write(STDERR_FILENO, error_message, strlen(error_message)); 
                                }
                }
        
        }
        return 0;
}
            

//batchmode takes an array, attempts to open a file and
int batchMode(char *argv[]) {
    int retO;
    int retBI;
        int retAC;
        int tokenLen;
        int k = 0;


    FILE *tokenFile;

        char *tokenArray[1024];
    char str[1024];

    tokenFile = fopen(argv[1], "r");
        printf("Opening file named %s\n", argv[1]);
    
    // Check if the file doesn't exist
    if( tokenFile == NULL) {
            //bad batch file
            write(STDERR_FILENO, error_message, strlen(error_message)); 
                        exit(1);
    }

        // If it exists, open it, read the line and tokenize it
    else {
        while( fgets( str, 1024, tokenFile) != NULL) {  //first line
                        char* p = strchr(str,'\n');
                if (p) {
                        *p = '\0';
                        char *lastToken = strtok( str, " "); 

                        //while there are words to tokenize
                        while( lastToken != NULL) {
                                                tokenArray[k] = lastToken;
                                                tokenLen++;     
                                                k++;
                                                lastToken = strtok( NULL, " "); //rest of the arguments
                                                                    
                        }
                                retAC = addCommands(tokenArray, tokenLen);
                                if(retAC != 0) {
                                                write(STDERR_FILENO, error_message, strlen(error_message));
                                                break;
                                }
                                else {
                                        printf("command is %s\n", commands[0]);
                                    // end of line - check first command for builtin
                                    retBI = checkBuiltIn(commands[0]);

                                    if( retBI == 7) {   //execute non builtin

                                                retO = executeOther(); 

                                                if (retO == 0) { //success
                                                        return 0;
                                                }
                                                printf("error executing %s\n", commands[0]);
                                                break;                             
                                         }

                                    else {
                                                executeBuiltIn(retBI);
                                        continue;
                                    }

                                    commandLen = 0;
                                    return 0; //return success
                                }
                        }
                        else { //eof error      
                                exit(0);
                                //write(STDERR_FILENO, error_message, strlen(error_message)); 
                        }
        }
    }
        write(STDERR_FILENO, error_message, strlen(error_message));
        exit(1);
}

int main(int argc, char *argv[]) {
        //initialise path[0] to bin, path[1] = NULL
        
    int retB;//batch mode return
    int retI; //interactive mode return
    //while(1) {
                if(argc == 1) {
                        while(1){
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
        }
        if(argc == 2) {
                        while(1) {
                        puts("entering batch mode...");
                        retB = batchMode(argv);
                
                        if(retB == 0 ) {
                            puts("Success!");
                            continue;
                        }
                        else {
                            break;
                        }
                        }
        }
    
        else {
            write(STDERR_FILENO, error_message, strlen(error_message));
            return 1; //return failure
        }
        //}
}
