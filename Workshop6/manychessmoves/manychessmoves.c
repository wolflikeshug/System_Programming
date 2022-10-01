//  A STANDARD SET OF HEADER FILES REQUIRED
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/param.h>                  // provides MAXPATHLEN
#include <sys/wait.h>
#include <sys/time.h>

//  written by Chris.McDonald@uwa.edu.au, Oct 2019-

//  A FAKE LIBRARY-FUNCTION
int numberOfCores(void) { return 8; }

//  RETURNS THE CURRENT TIME, AS A NUMBER OF MILLISECONDS, IN A 64-bit INTEGER
int64_t milliseconds(void)
{
    struct timeval  now;

    gettimeofday( &now, NULL );       // timezone not required, so we pass NULL
    return ((int64_t)now.tv_sec * 1000) + now.tv_usec/1000;
}

int64_t start_msecs;

void stats(int running, int ncores, int done, int max)
{
    time_t  now = milliseconds();

    printf("%li %i/%i running %i/%i complete\n\n",
            now - start_msecs,
            running, ncores, done, max);
}

//  ----------------------------------------------------------------------


int start_one(int n, char gamestate[], char goodmove[])
{
    int pid     = fork();

//  fork()-ING NEW PROCESSES
    switch (pid) {

//  ACCOUNT FOR fork() FAILING
    case -1:
        break;

//  CHILD PROCESS NEEDS TO RUN THE goodchessmove PROGRAM
    case  0: {

//  FORMAT EACH OUTPUT FILE'S NAME - WE DO NOT NEED TO OPEN/CREATE IT
	char outputfile[MAXPATHLEN];
	sprintf(outputfile, "%s-%i", goodmove, n+1);

//  OVERWRITE CURRENT PROCESS WITH NEW PROGRAM
        execl(  "./goodchessmove",      // on-disk location of program
                "goodchessmove",        // its argv[0]
                gamestate,              // its argv[1]
                outputfile,             // its argv[2]
                NULL
            );

//  ACCOUNT FOR THE execl() FAILING
        exit(EXIT_FAILURE);
        break;
    }

//  PARENT PROCESS
    default:
        printf("new child pid=%i\n", pid);
        break;
    }
    return pid;
}

//  ----------------------------------------------------------------------

int result          = 0;            // 0=success, 1=any_failures

void wait_for_one(void)
{
    int pid, status;

    if((pid = wait(&status)) > 0) {
        printf("child pid=%i, exit(%i)\n", pid, status);

//  ENSURE THAT TERMINATING CHILD PROCESS WAS SUCCESSFUL
        if(status != 0) {
            result      = 1;
        }
    }
}

//  ----------------------------------------------------------------------

int manychessmoves(int ninstances, char gamestate[], char goodmove[])
{
//  WELL-CHOSEN IDENTIFIER NAMES MAKE THE LOGIC EASIER TO READ
    int ncores          = numberOfCores();
    int nstarted        = 0;
    int nrunning        = 0;
    int nfinished       = 0;

//  2 NESTED WHILE STATEMENTS SUPPORT THE LOGIC (THERE MAY BE A SIMPLER WAY)

//  WHILE NOT YET FINISHED ALL INSTANCES.....
    while(nstarted < ninstances && result == 0) {

//  WHILE SOME CORES ARE SITTING IDLE...
        while(nrunning < ncores && nstarted < ninstances && result == 0) {

            if(start_one(nstarted, gamestate, goodmove) > 0) {
                ++nstarted;
                ++nrunning;
		stats(nrunning, ncores, nfinished, ninstances);
            }
        }                               // inner while loop

//  PARENT PROCESS WAITS FOR 1 PROCESS
        if(nrunning > 0 && result == 0) {
            wait_for_one();
            --nrunning;
            ++nfinished;
            stats(nrunning, ncores, nfinished, ninstances);
        }
    }                                   // outer while loop

//  WHEN ALL CHILDREN HAVE EVENTUALLY STARTED, OR AN ERROR IS DETECTED,
//  WE STILL NEED TO wait() FOR ANY REMAINING PROCESSES
    while( nrunning > 0) {
        wait_for_one();
	--nrunning;
	++nfinished;
	stats(nrunning, ncores, nfinished, ninstances);
    }
    return result;                      // 0=success, 1=any_failures
}

//  ----------------------------------------------------------------------

//  main() CHECKS ARGUMENTS, CALLS ANOTHER FUNCTION TO DO THE REAL WORK
int main(int argc, char *argv[])
{
    if(argc != 4) {
        fprintf(stderr, "Usage: N gamestate goodmove\n");
        exit(EXIT_FAILURE);
    }
    else {
        int ninstances  = atoi(argv[1]);
        start_msecs = milliseconds();

        return manychessmoves( ninstances, argv[2], argv[3] );
    }
    exit(EXIT_SUCCESS);
}
