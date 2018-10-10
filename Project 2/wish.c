#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *pathName[10]; //path char array

int main( int argc, char *argv[]) {
	FILE *tokenFile;
	char str[ 1024 ];
	char *lastToken;
	
	char *arr[ 25 ] = { 0 };
	char **ptr = arr;

	int j = 1;
	int k = 1;

	//if argc is 1, interactive mode
	if( argc == 1) {
		//do something;
	}
	/* Else check the arg vector for the filename*/
	else {
		tokenFile = fopen(argv[j], "r");
		
		/* Check if the file doesn't exist */
		if( tokenFile == NULL) {
			//write error
		}
//https://stackoverflow.com/questions/42795727/add-string-to-array-c-pointers	
		/* If it does, open it, read the line and tokenize it */
		else {
			while( fgets( str, 1024, tokenFile) != NULL) {
				//print line to stdout to confirm	
				fputs( str, stdout);

				lastToken = strtok( str, " "); //check return value of strtok
				ptr[k] = lastToken; //how to add string to array?
				//check if this will work strcpy(arr[k], lastToken)
				while( lastToken != NULL) {
					printf( "%s\n", lastToken);
					lastToken = strtok( str, " ");
                    ptr[k++] = lastToken;
				}
			}	
		}
		fclose( tokenFile);
	}
	return 0;
}