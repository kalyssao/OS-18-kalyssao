#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXCHAR 1000

int main(int argc, char *argv[]) {
	int j;
	char temp[MAXCHAR];
	char user[MAXCHAR];
	
	FILE *fileToSearch;
	FILE *userEntry;
	
	/* If there's no argument */ 
	if( argc <= 1) {
		printf("my-grep: searchterm [file ...]\n");
		exit(1);
	}

	/* Else if there's an argument but no file*/
	else if( argc == 2) {
		printf("Enter the text file: ");
		fgets(user, MAXCHAR, stdin);

		/* strip the newline character at the end */
		char* nl = strchr(user, '\n');
		if( nl != NULL) {
			*nl = '\0';		
		}		
		
		userEntry = fopen(user,"r");

		if( userEntry == NULL) {
			printf("my-grep: cannot open file\n");
			exit(1);
		}
		else {
				
			/* whilst there's text to search, search it */
			while( fgets( temp, MAXCHAR, userEntry) != NULL) {
					
				/*search each line of the text file for the argument*/ 
				if( (strstr(temp, argv[1])) != NULL) {
				
					/* if it's there, print the line */
					printf("%s", temp);
				}	
			}
		}		
	}
	
	/* Else if there are arguments */
	else {

		/* Check the length of the argv for items */
		for( j = 2; j < argc; ++j) {
			fileToSearch = fopen(argv[j],"r");

			/* Can it be opened? */			
			if( fileToSearch == NULL) {
				printf("my-grep: cannot open file\n");
				exit(1);	
			}
	
			else {
				
				/* whilst there's text to search, search it */
				while( fgets( temp, MAXCHAR, fileToSearch) != NULL) {
					
					/*search each line of the text file for the argument*/ 
					if( (strstr(temp, argv[1])) != NULL) {
						
						/* if it's there, print the line, increment counter */
						printf("%s", temp);
					}
				}
			}			
			fclose(fileToSearch);
		}
	}
	return(0);
}
