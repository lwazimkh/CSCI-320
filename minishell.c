#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1000
#define MAX_ARGS 64

int main(void){
    char line[MAX_LINE];    // input storage
    char *token;            // pointer for each token
    char *mutableinput;     // mutable pointer
    char *args[MAX_ARGS];   // array of pointers to tokens
    int argc;
    
    while(1){
    printf("user> ");   // shell prompt symbol
    fflush(stdout);
    // Reads a line of input
    if (fgets(line, sizeof(line), stdin) == NULL){
        printf("\n Exiting.\n");
        break;   // indicates an error or EOF
    }
    // remove the newline after each command
    line[strcspn(line, "\n")] = '\0';   
    
    // skips empty lines
    if (line[0] == '\0'){
        continue;
    }

    // a passable pointer that will be modified by strsep()
    mutableinput = line;
    argc = 0;

    // split the input by spaces
    while ((token = strsep(&mutableinput, " \t\n")) != NULL){
        if (*token == '\0') continue;   // skip all the empty tokens
        args[argc++] = token;
        if (argc >= MAX_ARGS -1) break;
    }

    args[argc] = NULL;

    // Fork a new child process
    pid_t p = fork();
    // Error case
    if(p < 0){
    perror("fork failed");
    continue;
    }
    // creates a child process that executes the command
    if (p == 0){
        execvp(args[0], args);
        // If execvp returns, an error occurred
        perror("execvp failed");
        exit(1);
    } else {
        // parent goes down this path (original process)
        int status; // parent waits for child to finish
        waitpid(p, &status, 0);
    }
  }
    return 0;
}