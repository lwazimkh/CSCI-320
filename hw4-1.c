#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

void forkFunction()
{
int x = 100;
// prints out x before Fork()
printf("Initial x value pre-Fork: %d (PID: %d)\n", x, getpid());

pid_t p = fork();
    // Error case
if(p < 0){
perror("fork failed");
exit(1);
}
    // creates a child process
else if (p == 0){
    printf("Orginal value of x: %d\n", x); // Prints x's original value
    printf("Child says x = %d (PID: %d)\n", ++x, (int) getpid());
    // child pre-increments x's value to 101
} else {
    // parent goes down this path (original process)
    int wc = wait(NULL); // parent waits for child to finish
    printf("Original value of x: %d\n", x); // Prints x's original value
    printf("Parent says x = %d (wc:%d)(PID: %d)\n", --x,wc, (int) getpid());
    // parent pre-decrement x's value to 99
}
}
int main()
{
forkFunction();
return 0;
}
// What value is the variable in the child process?
// The variable is 100 as it is inherited by the parent 

// What happens to the variable when both the child and parent change the value of x?
// Nothing happens to the variable because the child and parent make copies of the variable
// and change the values of the copies