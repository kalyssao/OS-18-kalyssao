#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define COMMAND_LEN 100
#define PARAM_LEN 10

FILE *path_file;
int is_builtin(char **params){
	return 0;
}

int parse_commands(char *cmd, char **params) {
	int paramCount = 0;
	int stat_loc;

	pid_t child_pid;
	
	char **paths[PARAM_LEN];
	// parse cmd string into params array untill NULL, then break
	for (int i = 0; i < PARAM_LEN; i++) {
		params[i] = strsep(&cmd, " ");
		printf("%s \n", params[i]);
		if(params[i] == '\0') break;
	}

	// break if exit was entered
	if(strcmp(params[0], "exit") == 0){
		exit(0);
	}

	// check other builtins (cd and path)
	if(strcmp(params[0], "cd") == 0)  {
		char *directory = "/";
		char *x = strcat(directory, params[1]);
		chdir(x);
		return 1;
	}

	if(strcmp(params[0], "path") == 0){
		path_file = fopen("paths.txt","w+");
		// adding to path var
		for (int k = 1; k < PARAM_LEN; k++) {
			paths[paramCount] = params[k];
			fprintf(path_file,"%s\n", paths[paramCount]);
			paramCount++;
			if(params[k] == '\0') break;
		}
		return 1;
	}

	child_pid = fork();
	if(child_pid == 0)	{
		evexvp(cmd, params);
	}
	else	{
		waitpid(child_pid, &stat_loc, WUNTRACED);
	}

	return 0;
}

int main(int argc, char const *argv[])
{
	char error_message[30] = "An error has occurred\n";
	FILE *token_file;
	char cmd[COMMAND_LEN];
	char *params[PARAM_LEN];

	//int cmdCount = 0;
   
   // interactive mode
	if(argc == 1)	{
		while(1){
			// print prompt
			fputs("wish> ", stdout);

			// check if empty user entry
			if(fgets(cmd, sizeof(cmd), stdin) == NULL) break;

			// check for newline, replace with null
			if(cmd[strlen(cmd)-1] == '\n') {
				cmd[strlen(cmd)-1] = '\0';
			}

			// parse command into parameter array
			parse_commands(cmd, params);

			//if(execute_cmd(params) == 0) break;
		}
		return 0;
	}
	
	// batch mode - open specified text file
	if(argc == 2)	{
		token_file = fopen(argv[1], "r");

		while(1) {
			fputs("batch mode", stdout);

			// check that file exists
			if(token_file == NULL) {
				write(STDERR_FILENO, error_message, strlen(error_message));
				exit(1);
			}

			while(fgets(cmd, sizeof(cmd), token_file) == NULL) fclose(token_file);
			parse_commands(cmd, params);
			if(strcmp(params[0], "exit") == 0) break;

			// exect
		}
	}
	
	/*else{ // neither - error
		return 1;
	} */

}
