#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


char error_message[30] = "An error has occurred\n";

//execute takes the whole line array and its size and uses the size to test parameter length
int executeBuiltIn( char *argv[], int size, char *paths[]) {

	int j = 1;
	int index = 0;
	
	char **pathNames = NULL;
	char str[ 1024 ];

	int ret;
	int len;
	//check if the command is exit, and if a parameter was passed to it or nah
	if( !strcmp( "exit", argv[0])) {
		if( size == 1) {
			exit(0);
		}
		else {
			write(STDERR_FILENO, error_message, strlen(error_message));
		}
	}
	//SLICE USER ENTRY ARRAY INTO PATH ARRAY AND COPY TO GLOBAL
	//check if the command is path, and if there are no, one or more args
	if( !strcmp( "path", argv[0])) {
		pathNames = realloc(pathNames, sizeof(char*)*(index+1));

		if( size == 1) { //no argument
			//shell should not be able to run any programs
			len = 0;
			//printf("The paths are %s\n", pathArray)
		}

		if( size == 2) { //one argument - add arg to path
			
			char *dup = malloc(strlen(argv[1])+1);
			strcpy(dup,argv[1]);
			pathNames[index++] = dup;
					
			len = 1;
			printf("The paths are %s\n", &pathNames);			
		}

		if( size >= 2) { //two arguments - string copy and concatenate the rest
			int i;
			len = size - 1;
//to size or size-1? is it null terminated?
			for( i = 1; i < size; ++i) {
				char *dup = malloc(strlen(argv[i])+1);
				strcpy(dup, argv[i]);
				strcat(dup, " ");
				pathNames[index++] = dup;

				strcat(pathArray[size - 1] , " ");	
				strcat(pathArray[size - 1], argv[i]);
			}
			printf("The paths are %s\n", &pathArray);
		}
	}
	
	//check if the command is cd, and if there's more/less than one arg
	if( !strcmp( "cd", argv[0])) {
		if( size != 2) {
			write(STDERR_FILENO, error_message, strlen(error_message)); 
		}
		else {	
			//printf("Executing %s on command %s", argv[0], argv[1]);

			for( int p = 0; p < len - 1; ++p) {
				inter = strcat(path[p], "/");
				dir = strcat(inter, argv[1]);
				ret = chdir(dir);
			
				if( ret != 0) {
					continue;
				}
				else {
					//successful!
					printf("Changed directory to %s\n", argv[1]);
					return len;
				}
			}
		}
	}
	else {
		//none were builtins
		return 0;
	}
	return 0;
}

int main( int argc, char *argv[]) {
	FILE *tokenFile;
	int j = 1;
	int index = 0;
	
	char *builtIns[] = {"exit", "cd", "path"};
	char **res = NULL;
	char str[ 1024 ];

	//if argc is 1, interactive mode
	if( argc == 1) {
		//do something;
		return 1;
	}

	// if argc is 2, batch mode
	if( argc == 2) {
		tokenFile = fopen(argv[j], "r");
		
		// Check if the file doesn't exist
		if( tokenFile == NULL) {
			//bad batch file
			write(STDERR_FILENO, error_message, strlen(error_message)); 
			exit(1);
		}
		// If it does, open it, read the line and tokenize it
		else {
			while( fgets( str, 1024, tokenFile) != NULL) {
				char *lastToken = strtok( str, " "); 
				
				while( lastToken != NULL) {
					res = realloc(res, sizeof(char*)*(index+1));
					char *dup = malloc(strlen(lastToken)+1);
					strcpy(dup,lastToken);
					res[index++] = dup;
					
					lastToken = strtok( NULL, " ");
					
				}
				
				res = realloc(res, sizeof(char*)*(index+1));
				res[index] = NULL;

				int size = index;

				
				//check if command is builtin
				for( int i = 0; i < 3; ++i) {
					//if current isn't, continue
					if( strcmp(res[0], builtIns[i]) != 0) {
						continue;
					}
					//else, execute the builtin
					executeBuiltIn(res, size);
					break;
				}

				//if we're here - its non-builtin
				//create child process and do things. 
				pid_t child_pid = fork();
				//child process
				if( child_pid == 0) {
					//for item in path, execute the function in 
					for( int p = 0; p < pathLen; ++p) {
						inter = strcat(path[i], "/");
						dir = strcat(inter, res[0]);
						if( execv(dir, res)) {
							//error
						} 
					}
				}
			}
			//check if EOF marker has been reached
			if( feof(tokenFile)) {
				exit(0);
			}
		}
		fclose( tokenFile);
		return 1;	
	}
	
	else {
		//more than one text file	
		exit(1);
	}
}
