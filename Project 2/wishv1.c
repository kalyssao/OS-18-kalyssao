#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXCHAR 1000
char builtIn[3];
/*int interactiveMode(void) {
	
	char user[MAXCHAR];
	while(1) {
		printf("wish> ");
		fgets(user, MAXCHAR, stdin);

		if(strstr(user, "exit")) {
			printf("Exiting..\n");
			break;
		}
	}
}*/

/*parse entry
int parseEntry
//tokenising entries into the array to be used
tok = strtok(line," ");
k = 0;
while( (tok = strtok(NULL, " ")) != NULL) {
	array_args[k] = tok 
	k++;
}

int checkBuiltIn(void){
	const char *pathNames = [`/bin'];
if( argv[i] == "exit") {
	exit(0)
if( argv[i] == "cd") {
	if( argc == 1) {
		chdir(argv[i+1]
	}
	else {
		exit(0)
	}
if( argv[i] == "path") {
	for( int j = 2; j < argc; ++j){
		access(
		
	}
}
}	
*/
//check for redirect - if array contains ">"
int main(int argc, char *argv[]) {
	char *buffer;
	size_t bufsize = 32;
	size_t characters;
	char error_message[30] = "An error has occurred\n";
	//write(STDERR_FILENO, error_message, strlen(error_message));

	buffer = (char *)malloc(bufsize * sizeof(char));

	if( buffer == NULL) {
		perror("Unable to allocate buffer");
		exit(1);
	}

	//interactive mode
	if( argc == 1) {
		/*char user[MAXCHAR];*/
		while(1) {
			printf("wish> ");
			characters = getline(&buffer, &bufsize, stdin);

			if(strstr(buffer, "exit")) {
				printf("Exiting..\n");
				break;
			}
			else {
				//create child process and execute
				fork();
				
			}
		}
	}
	
	//batch mode
	else {
		for( int i = 1; i < argc; ++i) {//i less than 1
			if( argv[i] == "exit") {
				exit(0)
			}
			if( argv[i] == "cd
		}	
	}	
}