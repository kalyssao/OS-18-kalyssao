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
char *redirectArray[20];
char *interArray[PARAM_LEN];

char redirect[600]="";
char parallel[600]="";
char filename[600] = "";

pthread_t threadArray[PARAM_LEN];

int execvp(const char *file, char *const argv[]); 
void *execute2();
int execute(char** params);

void redirection(){
	
	
	pid_t pid = fork();
	if( pid == 0)	{
		FILE *fw = fopen(filename,"w+");
		dup2(fileno(fw), 1);
		dup2(fileno(fw), 2);
		fclose(fw);
		execvp(redirectArray[0], redirectArray);
		//return 0;
	}
	else	{
		int stat;
		waitpid(pid, &stat, 0);
		//return 1;
	}
}

void* execute2(){
		pid_t child_pid = fork();
		if( child_pid == 0)	{
			execvp(interArray[0], interArray);
			//return 0;
		}
		else	{
			int x;
			waitpid(child_pid, &x, 0);
			//return 1;
		}
	
	}

	int execute(char ** params){
		pid_t child_pid = fork();
		if( child_pid == 0)	{
			execvp(params[0], params);
			return 0;
		}
		else	{
			int x;
			waitpid(child_pid, &x, 0);
			return 1;
		}
	
	}

void parse_commands(char *cmd, char **params) {
	int paramCount = 0;
	int stat_loc;

	pid_t child_pid;
	
	char **paths[PARAM_LEN];
	
	// parse cmd string into params array untill NULL, then break
	for (int i = 0; i < PARAM_LEN; i++) {
		params[i] = strsep(&cmd, " ");
		//interArray[i] = params[i];
		if(params[i] == '\0') break;

		if(strcmp(params[i], ">") == 0){
			strcpy(redirect, "yes");
		}

		if(strcmp(params[i], "&") == 0){
			strcpy(parallel, "sure");
		}
	}

	// break if exit was entered
	if(strcmp(params[0], "exit") == 0){
		//printf("%s", params[0]);
		exit(0);
	}

	else if(strcmp(parallel, "sure") == 0){
		int k =0;
		for(int i = 0; i < 10; i++){
			if(params[i]==NULL){
				pthread_create( &threadArray[i], NULL, execute2,  NULL);
				pthread_join( threadArray[i], NULL); 
				//execute(interArray);
				break;
			}
			if(strcmp(params[i], "&")!=0){
				interArray[k] = params[i];
				k++;
			}
			else{
				k =0;
				pthread_create( &threadArray[i], NULL, execute2,  NULL);
				pthread_join( threadArray[i], NULL); 
				//execute(interArray);
				memset(interArray, 0, sizeof (interArray));
				//printf("%s\n", interArray[0]);
			}
		}
	}

	else if(strcmp(redirect, "yes") == 0){
		for(int i = 0; i < PARAM_LEN; i++){
			if(strcmp(params[i], ">")!=0){
				redirectArray[i] = params[i];

			}
			else{
			strcpy(filename, params[i+1]);
			strcpy(redirect, "");
			redirection();
			break;	
			}
		}
		printf("%s\n", params[0]);
	
	}

	// check other builtins (cd and path)
	else if(strcmp(params[0], "cd") == 0)  {
		char directory[COMMAND_LEN] = "/";

		strcat(directory, params[1]);
		
		if( chdir(directory) != 0){
			write(STDERR_FILENO, error_message, strlen(error_message)); 
		}
		//return 1;
	}

	else if(strcmp(params[0], "path") == 0){
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
			//return 1;
	}

	//printf("%s\n", "kkkk");


	else if(execute(params)==0){
	 	exit(0);
	 }
	//return 0;
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
			//memset(params, 0, sizeof params);
		}
		//return 0;
	}
	
	// batch mode - open specified text file
	if(argc == 2)	{
		token_file = fopen(argv[1], "r");
		FILE *path_file = fopen("pathfile.txt","r");

		while(1) {
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
	
	else{ // neither - error
		puts("problem");
	}

}
