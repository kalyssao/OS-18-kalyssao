#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


char error_message[30] = "An error has occurred\n";

//execute takes the whole line array and its size and uses the size to test parameter length
int executeBuiltIn( char *argv[], int size) {
	char **pathArray = malloc(0);
	int ret;
	//check if the command is exit, and if a parameter was passed to it or nah
	if( !strcmp( "exit", argv[0])) {
		if( size == 1) {
			exit(0);
		}
		else {
			write(STDERR_FILENO, error_message, strlen(error_message));
		}
	}

	//check if the command is path, and if there are no, one or more args
	if( !strcmp( "path", argv[0])) {
		if( size == 1) { //no argument
			//shell should not be able to run any programs
		}

		if( size == 2) { //one argument - string copy
			//strcpy(pathArray, argv[1]);
			pathArray = realloc(pathArray, size * sizeof (char*));
			pathArray[size - 1] = malloc(100 * sizeof(char));
			strcpy(pathArray[size - 1], argv[1]);
					
		}

		if( size >= 2) { //two arguments - string copy and concatenate the rest
			int i;
			pathArray = realloc(pathArray, size * sizeof (char *));
			strcpy(pathArray[size - 1], argv[1]);

			for( i = 2; i < size; ++i) {
				pathArray = realloc(pathArray, size * sizeof (char*));
				pathArray[size - 1] = malloc(100 * sizeof(char));
				strcat(pathArray[size - 1] , " ");	
				strcat(pathArray[size - 1], argv[i]);
			}
		}
	}
	
	//check if the command is cd, and if there's more/less than one arg
	if( !strcmp( "cd", argv[0])) {
		if( size != 2) {
			write(STDERR_FILENO, error_message, strlen(error_message)); 
		}
		else {	
			printf("Executing %s on command %s", argv[0], argv[1]);
			gdir = 
			for item in path array, check if chdir works for a given path
			ret = chdir(argv[1]);
			printf("%i", ret);
			if( ret != 0) {
				write(STDERR_FILENO, error_message, strlen(error_message));
			}
			else {
				//successful!
				printf("Changed directory to %s\n", argv[1]);
				return 1;
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

	/*char str[ 1024 ];
	char *lastToken = NULL;
	char **array = malloc(0);*/
	char *builtIns[] = {"exit", "cd", "path"};
	
	//int ret;
	int j = 1;
	int index = 0;
	char **res = NULL;
	char str[ 1024 ];

	//if argc is 1, interactive mode
	if( argc == 1) {
		//do something;
		return 1;
	}

	// if argc is 2, batch mode
	if( argc == 2) {
		//printf("%i\n",argc);
		tokenFile = fopen(argv[j], "r");
		
		/* Check if the file doesn't exist */
		if( tokenFile == NULL) {
			//bad batch file
			write(STDERR_FILENO, error_message, strlen(error_message)); 
			exit(1);
		}
		/* If it does, open it, read the line and tokenize it */
		else {
			while( fgets( str, 1024, tokenFile) != NULL) {
				//print line to stdout to confirm	
				//puts( str, stdout);

				char *lastToken = strtok( str, " "); 
				//check return value of strtok
				while( lastToken != NULL) {
					//size++;
					res = realloc(res, sizeof(char*)*(index+1));
					char *dup = malloc(strlen(lastToken)+1);
					strcpy(dup,lastToken);
					res[index++] = dup;

					/*array = realloc(array, size * sizeof (char*));
					array[size - 1] = malloc(100 * sizeof(char));
					strcpy(array[size - 1], lastToken);
					*/
					lastToken = strtok( NULL, " ");
					
				}
				res = realloc(res, sizeof(char*)*(index+1));
				res[index] = NULL;
				int size = index;

				/*for( int k = 0; res[k]; ++k){				
					printf("%s\n", res[k]);
				}*/
				
				//iterate through builtins - check if command is builtin
				for( int i = 0; i < 3; ++i) {
					//if they arent equal, continue
					if( strcmp(res[0], builtIns[i]) != 0) {
						continue;
					}
					//else, call the line array and execute the builtin
					//printf("executing builtin..%s\n", res[0]);
					executeBuiltIn(res, size);
					break;
				}

				//non-builtin: create child process and do plenty things. 			
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