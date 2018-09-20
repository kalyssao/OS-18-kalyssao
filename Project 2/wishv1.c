#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

//int batchMode(void){}

int main(int argc, char *argv[]) {
	/* FILE *userEntry; */
	
	//interactive mode
	if( argc == 1) {
		char user[MAXCHAR];
		while(1) {
			printf("wish> ");
			fgets(user, MAXCHAR, stdin);

			if(strstr(user, "exit")) {
				printf("Exiting..\n");
				break;
			}
		}
	}
	//batch mode
	else {
		for( int i = 1, i < argc, ++i) {
		
}
		
}	
}

	
}	
}
