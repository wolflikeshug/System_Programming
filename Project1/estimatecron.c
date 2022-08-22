#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LIST_SIZE 21
#define MAX_LINE_SIZE 101
#define MAX_COMMAND_SIZE 41

int month;
char *crontab_file;
char *estimates_file;

FILE *dict;
int i;
char *buffer;
char command[MAX_LINE_SIZE];
char cron_command[MAX_LIST_SIZE][MAX_COMMAND_SIZE];

// Function: read_command_file
// Description: Reads the command from crontab-file and stores it in an array
void read_crontab_file() {
    dict = fopen(crontab_file, "r");
    // print Error if file does not exist
    if (dict == NULL) {
        printf("Error: File not found.\n");
        exit(EXIT_FAILURE);
    }
    // read the file line by line
    i = 0;
    while( fgets(command, MAX_LINE_SIZE, dict) != NULL ) {
        //if command start with "#" then skip it
        if (command[0] == '#') {
            continue;
        }
        strcpy(cron_command[i], command);
        i++;
    }
    fclose(dict);
}

// Function: read_estimates_file
// Description: Reads the estimates from estimates-file and append the estimates time behind the command

int main(int argc, char* argv[]) {
    crontab_file = argv[2];
    estimates_file = argv[3];
    read_crontab_file(cron_command);
    for (i=0; i<MAX_LIST_SIZE; i++) {
        printf("%i: %s", i, cron_command[i]);
    }
    return 0;
}