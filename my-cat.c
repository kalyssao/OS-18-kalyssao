#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* add/remove '*' if it doesnt work 

static const char filename[] = argv[j];
*/

int main(int argc, char *argv[]){
	FILE *fileToCopy;
	char str[60];
	int j;
	
	/* Checking if no file is specified */
	if( argc == 1) {
		exit(404);
		return(0);
	}
	/* Else, iterate through the arg vector and use each filename*/
	else {
		for( j = 1; j < argc; ++j) {
			fileToCopy = fopen(argv[j], "r");
		
			/* Check if the file doesn't exist */
			if( fileToCopy == NULL) {
				fprintf("my-cat: cannot open file \n");
				exit(1);
			}
			
			/* If it does, do stuff*/
			if( fgets(str, 60, fileToCopy) != NULL) {
				fputs(str, fileToCopy);
				printf("%s",str);
				fclose(fileToCopy);
				return(0);
			}
		}
	}
	return(0);
}
/* If content not empty - if( fgets(str, 60, fileToCopy) != NULL) {*/