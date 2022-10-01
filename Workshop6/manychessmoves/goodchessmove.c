#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if(argc != 3) {
        fprintf(stderr, "Usage: %s gamestate chosenmove\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    printf("%40s hello from '%s', pid=%i\n", "", argv[0], getpid() );

    FILE *fp = fopen(argv[2], "w");

    if(fp != NULL) {
        srand( getpid() );              // seed the random number generator

        int seconds = rand() % 5 + 2;
        sleep(seconds);                 // hmmm, thinking about chess....

        fprintf(fp, "pid=%i, thought for %i seconds\n", getpid(), seconds );
        fclose(fp);
        exit(EXIT_SUCCESS);
    }
    exit(EXIT_FAILURE);
}
