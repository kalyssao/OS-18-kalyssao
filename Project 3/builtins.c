#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define PATH_LEN 10

FILE *path_file;

int wish_cd(char **args);
int wish_path(char **args, int argc);

char path[PATH_LEN] = "/bin"; //{'/bin', '\0'};

struct Builtin {
    char* name;
    int (*func) (char**);
};

struct Builtin builtins[] = {
    { "cd", &wish_cd },
    { "path", &wish_path }
};

int main(int argc, char *argv[]){
    while(1){
        if(strcmp(argv[1], "path") == 0){
            wish_path(argv, argc);
        }
        if(strcmp(argv[1], "cd") == 0){
            puts("directory");
            wish_cd(argv);
        }
        else{
            exit(1);
        }
        break;
    }
}

int wish_cd(char **args) {
    puts("Changing directory");
    if (args[2] == NULL) {
        fprintf(stdout, "lsh: expected argument to \"cd\"\n");
    } 
    else {
        if (chdir(args[2]) != 0) {
            perror("lsh");
        }
    }
  return 1;
}

int wish_path(char **args, int argc) {
    //intialise path file
    path_file = fopen("pathfile.txt", "w");

    //check if path file exists/is open
    if (path_file == NULL){
        //write error, break
    }

    //empty path argument
    if (argc == 2 ) fopen("pathfile.txt", "w");
    
    //one path or more - print paths into each line
    if (argc > 2) {
        for (int i = 2; i < argc; i++) {
        fprintf(path_file, "%s\n", args[i]);
        }
    }

    //else less than 2 - error
    else {
        exit(0);
    }
    fclose(path_file);
    return 1;
}