#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int status1, status2;
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
	    sleep(1);
        exit(0);
    } else {
        
        int rc2 = fork();
        if (rc2 < 0){
            // fork failed; exit
            fprintf(stderr, "child2 fork failed\n");
            exit(1);
        } else if (rc2 == 0){
            //child 2 (new process)
            printf("hello, I am child2 (pid:%d)\n", (int) getpid());
            sleep(1);
            exit(0);
        }
        // Parent process waits for both children
        printf("Parent process (PID: %d) waiting for children.\n", getpid());

        waitpid(rc2, &status2, 0);
        if (WIFEXITED(status2)) {
            printf("child2 (PID: %d) exited with status %d.\n", rc2, WEXITSTATUS(status2));
        }

        printf("Parent (PID: %d) is finished.\n", getpid());
    }
    return 0;
}