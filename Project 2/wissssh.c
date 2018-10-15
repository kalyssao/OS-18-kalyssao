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

char *path[900];

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
	char buf[1024];

    printf("command length is %d\n", commandLen);
    char *dir;
	char *gdir;
	char *inter;

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
		printf("time for cd\n");
		if(commandLen == 2) {
			while(*path[i] != '\0') {


				gdir = getcwd(buf, sizeof(buf));
            	inter = strcat(gdir, "/");
            	dir = strcat(inter, commands[1]);

            	
				retCH = chdir(dir);
				//printf("directory is %s\n", &dir[0]);

            	if(retCH != 0) {
                //failure - incorrect path maybe?
                	i++;
                	continue;
				}

            	else {
                	//change was successful - break
                	printf("Successfully changed directory to %s\n", commands[1]);
					return;
            	}
        	}
			write(STDERR_FILENO, error_message, strlen(error_message));
			return;
		}
		//more or less than 1 parameter
        write(STDERR_FILENO, error_message, strlen(error_message));
		return;
    }

    if(a == 8) {  //path - check if zero or more
        printf("path changing\n");
		printf("still %d\n", commandLen);
		/*if(commandLen == 2) { //no arg - run nothing except builtin
            //path[0] = '\0'; //should the whole path be equated to NULL?
            printf("You can only run builtins");
        }*/
        
		if(commandLen == 3) { //one arg - overwrite current path
		//could use an assignment, commands[i] = new_path
		//make others NULL
			
            //path[0] = commands[1];// = 
			//path[0] = commands[1];
			printf("test");
        }

        else {
            while(*path[i] != '\0') {  //two for loops - first is
                for(j = 1; j < commandLen; ++j) { //at index 1, the first path to be copied
                    path[i] = commands[j]; //overwriting the contents of the path
                    i++;
                }
                path[i] = '\0';
            }
        }
    }
	return;
}

//if not builtin - execute
int executeOther() {
    int i = 0;
    int retEO;
	printf("executing other command %s with length %d\n", commands[0], commandLen);
    pid_t c_pid;

    c_pid = fork();
    if(c_pid == 0) {
		while(*path[i] != '\0') {
			if(access(path[i], X_OK) != 0) { //path is legit
				    i++;
					continue;		
			}
			else {
				retEO = execvp(commands[0], commands); //execvp given command
				
				if(retEO == -1) {
					printf("there was a problem..");	    
				}

				else {
					printf("success");
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
						
        				retBI = checkBuiltIn(commands[0]);

        				if( retBI != 7){
            				executeBuiltIn(retBI); //execute builtin depending on return value
            				//continue;
        				}

						else {
							retEO = executeOther(); //execute non builtin
							if(retEO == 0) {
								printf("Success!");
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
    while(1) {
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
					
				    // end of line - check first command for builtin
				    retBI = checkBuiltIn(commands[0]);

				    if( retBI == 7) {	//execute non builtin

						retO = executeOther(); 

						if (retO == 0) { //success
							printf("success");
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
}

int main(int argc, char *argv[]) {
	//initialise path[0] to bin, path[1] = NULL
	path[0] = "/bin";
	path[1] = '\0';
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
