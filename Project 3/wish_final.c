#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define COMMAND_LEN 100
#define PARAM_LEN 10

char error_message[30] = "An error has occurred\n";

int redirect(char **params);
int execvp(const char *file, char *const argv[]); 

pthread_t threads[PARAM_LEN];
char cmds[COMMAND_LEN];

int parse_commands(char *cmd, char **params) {
	int paramCount = 0;
	int stat_loc;
	int t1;

	pid_t child_pid;
	
	char **paths[PARAM_LEN];
	// parse cmd string into params array untill NULL, then break
	for (int i = 0; i < PARAM_LEN; i++) {
		params[i] = strsep(&cmd, " ");
		strcpy(cmds[i], params[i]);
		if(params[i] == '\0') break;
		if(params[i] == '>'){
			//redirection
			int fw = open(params[i+1], O_APPEND|O_WRONLY);
			/* child_pid = 
			for(int k = 0; k < i; ) */
		}
		if(params[i] == '&'){
			child_pid = 
		}
		else continue;
	}
	// break if exit was entered
	if(strcmp(params[0], "exit") == 0){
		exit(0);
	}

	// check other builtins (cd and path)
	if(strcmp(params[0], "cd") == 0)  {
		char directory[COMMAND_LEN] = "/";

		strcat(directory, params[1]);
		
		if( chdir(directory) != 0){
			write(STDERR_FILENO, error_message, strlen(error_message)); 
		}
		return 1;
	}

	if(strcmp(params[0], "path") == 0){
		FILE *path_file = fopen("pathfile.txt","w+");

		if (path_file == NULL)	{
		    write(STDERR_FILENO, error_message, strlen(error_message)); 
		}

		// adding to path file
		for (int k = 1; k < PARAM_LEN; k++) {

			//paths[paramCount] = &params[k];
			if(params[k] == '\0') break;
			fprintf(path_file,"%s\n", params[k]);
			
		}
		fclose(path_file);
		return 1;
	}
	
	child_pid = fork();
	if( child_pid == 0)	{
		fprintf(stdout, "Executing %s\n", params[0]);
		execvp(params[0], params);
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

	int cmdCount = 0;
   
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
		}
		return 0;
	}
	
	// batch mode - open specified text file
	if(argc == 2)	{
		token_file = fopen(argv[1], "r");
		FILE *path_file = fopen("pathfile.txt","r");

		while(1) {
			fputs("batch mode\n", stdout);

			// check that file exists
			if(token_file == NULL) {
				write(STDERR_FILENO, error_message, strlen(error_message));
				exit(1);
			}

			while(fgets(cmd, sizeof(cmd), token_file) == NULL) fclose(token_file);
			parse_commands(cmd, params);
			if(strcmp(params[0], "exit") == 0) break;
		}
	}
	
	/*else{ // neither - error
		return 1;
	} */

}


// if ampersand = create thread
int pthread_create(pthread_t * thread, const pthread_attr_t * attr, void * (*start_routine)(void *), void *arg);
int pthread_join(pthread_t th, void **thread_return);
void pthread_exit(void *retval);

if(params[i] == "&"){
	for(int k = 0; k < i; k++){

	}
}