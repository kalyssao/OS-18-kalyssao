#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXCHAR 1000

int iterateOnEntry

int main(int argc, char *argv[]) {
	int j;
	int found = 0;
	char temp[MAXCHAR];
	char user[MAXCHAR];
	
	FILE *fileToSearch;
	FILE *userEntry

	/* If there's no argument */ 
	if( argc <= 1) {
		printf("my-grep: searchterm [file ...]\n");
		exit(1);
	}

	/* Else if there's an argument but no file*/
	else if( argc == 2) {
		printf("Enter the text file: ");
		userEntry = fgets(user, MAXCHAR, stdin);
	}
	
	/* if empty string */

	/* Else if there are arguments */
	else {

		/* Check the length of the argv for items */
		for( j = 2; j < argc; ++j) {
			fileToSearch = fopen(argv[j],"r");	\

			/* Can it be opened? */			
			if( fileToSearch == NULL) {
				printf("my-grep: cannot open file \n");
				exit(1);	
			}
	
			else {
				
				/* whilst there's text to search, search it */
				while( fgets( temp, MAXCHAR, fileToSearch) != NULL) {
					
					/*search each line of the text file for the argument*/ 
					if( (strstr(temp, argv[1])) != NULL) {
					
						/* if it's there, print the line, increment counter */
						printf("%s", temp);
						found++;
					}
					
				}
				
				if( found == 0) {
					printf("Argument cannot be found \n");
				}
			
			}
			fclose(fileToSearch);
			
		}
	}
return(0);
}
