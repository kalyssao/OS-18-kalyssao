//Kalyssa A. Owusu
//OS Lab 3
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>

#define MAXCHAR 200

char *userEntry;
char pathNames[MAXCHAR] = "/bin";
char tokenArray[MAXCHAR] = { 0 };
char error_message[30] = "An error has occured \n";

char 

int ret;

size_t tokenLength = sizeof(tokenArray)/sizeof(tokenArray[0]);

int checkBuiltIn();
int countWords(char str[]);
int addToPath();
char **tokenizeEntry(char *userEntry);
int checkBuiltIn();

//count the user entry to use the var for looping
int countWords(char str[]) {
        int count = 0, i;
        
        scanf("%[^\n]s", str);

        for (i = 0;str[i] != '\0';i++) {
                if (str[i] == ' ') {
                        count++;
                }
        }
        return count;    
}

//add to path function
int addToPath(){
    printf("Token length is %li\\n", tokenLength);
        for( int j = 1; j < tokenLength; ++j) {
                for( int k = 0; k < tokenLength; ++k) {
                        pathNames[k] = tokenArray[j];
                }
        }
        puts("Successfully added to path.");
        printf("Token length is %li\\n", tokenLength);
        return 0;
}

//tokenize entry and check if it's builtin
char **tokenizeEntry(char *userEntry) {
        int position = 0;
        int count = 1;
        int bufsize = 72;

        char *token = strtok(userEntry, " ");
        char **tokens = malloc(bufsize * sizeof(char*));
        
        while( token != NULL) {
                tokenArray[position] = token;
                position++;
                
                if( position >= bufsize) {
                        bufsize += bufsize;
                        tokens = realloc(tokens, bufsize * sizeof(char*));
                }
                token = strtok(NULL, " ");      
        }
        tokens[position] = NULL;
        count = count + position;
        return tokens;
}

//check if argument is a builtin function
int checkBuiltIn() {
        int ret;
        //no entry produces error message
        if( tokenLength == 0) {
                write(STDERR_FILENO, error_message, strlen(error_message));
        }
        //command only - either exit or path w/ no arg
        if( tokenLength == 1) {
                if( !strcmp(tokenArray[0], "exit")) {
                        exit(0);
                }
                if( !strcmp(tokenArray[0], "path")) {
                        //shell should not be able to run
                }
        }
        //not 0 or 1 - must be cd, path with more args, or error
        if( !strcmp(tokenArray[0], "cd")) {
                ret = chdir(tokenArray[1]);
                puts("Changing the current working directory");
                                
                if( ret != 0) {
                        write(STDERR_FILENO, error_message, strlen(error_message));
                        exit(0);
                }
        }
        if( !strcmp(tokenArray[0], "path")) {
                addToPath();
        }
        else{
                write(STDERR_FILENO, error_message, strlen(error_message));
        }
        
        return 0;
}

//main function
int main(int argc, char *argv[]){
        int memoryRead;
        //int nbytes = 200;
        
        pid_t c_pid, pid;
        int status;
        
        char execArgs[MAXCHAR] = ""; 
        //userEntry = (char *)malloc(nbytes + 1);
        char *userEntry = NULL;
        ssize_t bufsize = 0;

        size_t directoryLength = sizeof(pathNames)/sizeof(pathNames[0]);

        //interactive mode - one argument
        if( argc == 1) {
                while(1) {
                        puts("wish> ");
                        memoryRead = getline(&userEntry, &bufsize, stdin);
                        if( memoryRead == -1) {
                                write(STDERR_FILENO, error_message, strlen(error_message));
                        }
                        if( memoryRead != -1) {
                                //tokenize entered data, check if builtin
                                tokenizeEntry(userEntry);
                                ret = checkBuiltIn();
                                //copy tokens into arg with '\0' - check token array!
                                //execArgs = 
                                //it's not builtin, create fork and execute (TRY & MAKE FUNCTION)
                                if( ret != 5) {
                                        
                                        c_pid = fork();
                                        //execute within child process
                                        if( c_pid == 0) {
                                        //check whether file exists in given directory  error: ‘directoryLength’ undeclared (first use in this function)
                                                //for (int x = 0; x < directoryLength; ++x) {
                                                        if( access(pathNames[x], X_OK) == 0) {
                                                                //check if given args can execute
                                                                if( execvp(exexcArgs[0], execArgs) != -1) {
                                                                        break;
                                                                }
                                                        } 
                                                        break;
                                        
                                                        if( exec == -1) {
                                                                write(STDERR_FILENO, error_message, strlen(error_message));
                                                        }
                                                } 
                                                
                                                write(STDERR_FILENO, error_message, strlen(error_message));
                                        }
                                        //parent process waits for child to finish
                                        else if( c_pid > 0) {
                                                if( (pid = wait(&status)) < 0){
                                                        perror("wait");
                                                }
                                        
                                        }
                                }
                                //if(argc >= 2) {
                                //how does argc/argv work with interactive mode?
                                //check !
                                //if it uses argv/argc loop through..
                                                
                                                //if it doesn't - 
                                //for( int i = 0; i < argc; ++i)
                        }
                }
                //for( int i = 0; i < argc; ++i) {
                        
                }
        } 
/*expected identifier or ‘(’ before ‘if’
  if( argc > 1) {*/
        //batch mode - read through file specified argc > 1
        if( argc > 1) {
                char *filename = argv[1];
                FILE *fp = fopen(filename, "rb");
                int c;
                
                if (fp == NULL){
                        return 0;
                }

                while( fgets(userEntry, 150, fp) == NULL) {
                        tokenizeEntry(userEntry);
                        ret = checkBuiltIn();
                }
                exit(0);
                fclose(fp);
        }
