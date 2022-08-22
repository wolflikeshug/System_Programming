#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#define MAX_LIST_SIZE 21
#define MAX_COMMAND_SIZE 41

int month;
char *crontab_file;
char *estimates_file;

FILE *dict;
int i;
char *buffer;
char command[MAX_COMMAND_SIZE];
char cron_command[MAX_LIST_SIZE][2][MAX_COMMAND_SIZE];

// Function: read_command_file
// Description: Reads the command from file called "crontab"
void read_crontab_file() {
    dict = fopen(crontab_file, "r");
    i = 0;
    while( fgets(command, MAX_COMMAND_SIZE, dict) != NULL ) {
        //if command start with "#" then skip it
        if (command[0] == '#') {
            continue;
        }
        strcpy(cron_command[i][1], command);
        i++;
    }
    fclose(dict);
}

int main(int argc, char* argv[]) {
    crontab_file = argv[2];
    estimates_file = argv[3];
    read_crontab_file(cron_command);
    for (i=0; i<MAX_LIST_SIZE; i++) {
        printf("%i: %s", i, cron_command[i][1]);
    }
    return 0;
}