//Kalyssa A. Owusu
//OS Lab 3
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <process.h>

#define MAXCHAR

char *userEntry;
char pathNames[MAXCHAR] = '/bin';
char tokenArray[MAXCHAR] = '';
char error_message[30] = "An error has occured \n";

int ret;

size_t tokenLength = sizeof(tokenArray)/sizeof(tokenArray[0]);

//add to path function
int addToPath(){
	for( int j = 1; j < tokenLength; ++j) {
		for( int k = 0; k < tokenLength; ++k) {
			pathNames[k] = tokenArray[j];
		}
	}
	puts("Successfully added to path.");
	return(0);
}

//tokenize entry and check if it's builtin
int tokenizeEntry(char str[]) {
	char *token;
	char rest = str;
	
	for( int i = 0; i < tokenLength; ++i) {
		while( token = strtok_r(rest, " ", &rest)) {
		tokenArray[i] = token;
		}
	}
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
		if( tokenArray[0] == 'exit') {
			exit(0);
		}
		if( tokenArray[0] == 'path') {
			//shell should not be able to run
		}
	}
	//not 0 or 1 - must be cd, path with more args, or error
	if( tokenArray[0] == 'cd') {
			for(int l = 0; l < dirLength; ++l) {
				ret = chdir(tokenArray[1]);
				puts("Changing the current working directory");
				
				if( ret != 0) {
					write(STDERR_FILENO, error_message, strlen(error_message));
				}
			}
		}
	if( tokenArray[0] == 'path') {
		addToPath();
	}
	else{
		write(STDERR_FILENO, error_message, strlen(error_message));
	}

//if successful return 5	

}

//main function
int main(int argc, char *argv[]){
	int memoryRead;
	int nbytes = 200;
	
	pid_t c_pid, pid;
	int status;
	
	char execArgs[MAXCHAR] = ""; 
	userEntry = (char *)malloc(nbytes + 1);
	
	size_t directoryLength = sizeof(pathNames)/sizeof(pathNames[0]);

	//interactive mode - one argument
	if( argc == 1) {
		while(1) {
			puts("wish> ");
			memoryRead = getline(&userEntry, &nbytes, stdin);
			if( memoryRead == -1) {
				write(STDERR_FILENO, error_message, strlen(error_message));
			}
			if( memoryRead != -1) {
				//tokenize entered data, check if builtin
				tokenizeEntry(userEntry);
				ret = checkBuiltIn();
				//copy tokens into arg with '\0' - check token array!
				execArgs = 
				//it's not builtin, create fork and execute (TRY & MAKE FUNCTION)
				if( ret != 5) {
					
					c_pid = fork();
					//execute within child process
					if( c_pid == 0) {
						//check whether file exists in given directory
						for (int x = 0; x < directoryLength; ++x) {
							if( access(pathNames[x], X_OK) == 0) {
								//check if given args can execute
								if( execv(pathNames[x], execArgs) != -1) {
									break;
								}
							} 
							break; 
							sif( exec == -1) {
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
		for( int i = 0; i < argc; ++i) {
			
		}
	}
	//batch mode - read through file specified argc > 1
	else if( argc > 1) {
		char *filename = argv[1];
		FILE *fp = fopen(filename, "rb");
		int c;
		
		if (fp ==NULL){
			return 0;
		}

		while( fgets(userEntry, 150, fp) == NULL) {
			tokenizeEntry(userEntry);
			ret = checkBuiltIn();
		}
		exit(0);
		fclose(fp);
	}
}