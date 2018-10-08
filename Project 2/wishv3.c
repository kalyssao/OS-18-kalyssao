#define MAX_BUFFER 1024
#define MAX_ARGS 64
#include <string.h>
#include <stdio.h>

void checkBuiltIn(char str[]);

int main(int argc, char ** argv) {
	char buf[MAX_BUFFER];
	char * args[MAX_ARGS];
	char ** arg;

	int ret;

	while( !feof(stdin)) {
		
		fputs("wish> ", stdout);
		if( fgets(buf, MAX_BUFFER, stdin)) {

			
			
			if (args[0]){
				ret = checkBuiltIn(args[0]);
			}
		}
	}
}

int checkBuiltIn(char str[]) {
	char * builtIns[] = { "cd", "help", "exit"};
	int len = sizeof(builtIns)/sizeof(builtIns[0]);
	
	char arg[] = {0};
	strcpy(arg, str);
	for(int i = 0; i < len; ++i) {	
		if (!strcmp(arg, builtIns[i])) {
			fputs("It's here", stdout);
			
			return 1;
		}	
	}
}
				
