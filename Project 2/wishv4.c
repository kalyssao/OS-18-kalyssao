#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

char path[] = {0};
int addToPath(char str[]);
int executeCommand(char str[]);
int isBuiltInCommand(char str[]);
int executeBuiltInCommand(char str[]);
int scan_s(char *str, int str_len, int *s, int *e, const char delim);

int main (int argc, char **argv) {
	int childPid;
	size_t nbytes = 1000;
	int parsed;
	
	char *cmdLine;
	char *info;
	
	char command[200];
	
	command = (char *)malloc(nbytes+1);
	
	
	//interactive mode - always print out prompt and get the user entry
	if (argc == 1){
		while (1){
			printf("wish> ");
			fgets(command, sizeof command, stdin);
			
			//initialise parser
			int str_len = strlen(command);
			int tok_len = 0, s = 0, e = 0;
			char *tok;

			while (scan_s(test, str_len, &s, &e, ';') >= 0 ) {
        			int ss = 0, ee = 0;
        			while (scan_s(test + s, e-s, &ss, &ee, ',') >= 0 ) {
            				tok = (char *) malloc((ee-ss + 1) * sizeof(char));
            				char *dst = stpncpy(tok, test + s + ss, ee-ss);
            				tok[ee-ss]='\0';
            				printf("%d %s\n", ee-ss, tok);
            				ss = ee + 1;
            				free(tok);
        			}
        			s = e + 1;
    			}
    			return 0;
			
			//first token is the command
			info = &(commandTok[0]);
			size_t commandLen = sizeof(commandTok)/sizeof(commandTok[0]);
	 
			if ( isBuiltInCommand(info) == 1){
				executeBuiltInCommand(info);
			} 
			else {		
				childPid = fork();
				if (childPid == 0){
					executeCommand(info); //calls execvp  
				
				} 
				else {cd
					waitpid(childPid, NULL, 0);
				}
			}
		}
	}
	//batch mode
	if (argc > 1) {
		
	}
	return 1;
}

int addToPath(char str[]){
	return 1;
}

int isBuiltInCommand(char str[]) {
	char *builtInCommands[] = {"exit", "cd", "path"};
	int len = sizeof(builtInCommands)/sizeof(builtInCommands[0]);
	
	str =(char *)malloc(10 * sizeof(char));
	
	char arg[] = {0};
	strcpy(arg, str);
	
	for(int i = 0; i < len; ++i) {	
		if (!strcmp(arg, builtInCommands[i])) {
			fputs("It's here", stdout);
			
			return 1;
		}
		break;
	}
	return 0;
}

int executeBuiltInCommand(char str[]) {
	return 1;
}

int executeCommand(char str[]){
	return 1;
}

/*int scan_s(char *str, int str_len, int *s, int *e, const char delim) {
    if (*e == str_len)
        return -1;
    for (*e = *s; *e <= str_len; *e+=1) {
        if ((str[*e] == delim) || (*e == str_len)) {
            return *e - *s;
        }
    }
    return -2;
}*/
