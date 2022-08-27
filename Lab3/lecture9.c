#include  <stdio.h>
#include  <unistd.h>
#include  <stdlib.h>

void main()
{
    int  pid;                 // some systems define a pid_t

    switch (pid = fork()) {
    case -1 :
        printf("fork() failed\n");     // process creation failed
        exit(EXIT_FAILURE);
        break;

    case 0:                   // new child process
        printf("c:  value of pid=%i\n", pid);
        printf("c:  child's pid=%i\n", getpid());
        printf("c:  child's parent pid=%i\n", getppid());
        break;

    default:                  // original parent process
        sleep(1);
        printf("p:  value of pid=%i\n", pid);
        printf("p:  parent's pid=%i\n", getpid());
        printf("p:  parent's parent pid=%i\n", getppid());
        break;
    }
    fflush(stdout);
}