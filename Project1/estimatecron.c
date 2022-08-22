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
int total_cron_lines;
int *count_list;
char *command;
char *cron_line;
char *estimate_line;
char **cron_command;

// Fuctions: strext(char *, char *)
// Description: Returns True if string2 contained in string1
bool strext(char *string1, char *string2) {
    int i;
    for (i = 0; i < strlen(string1); i++) {
        if (string1[i] == string2[0]) {
            if (strncmp(string1 + i, string2, strlen(string2)) == 0) {
                return true;
            }
        }
    }
    return false;
}

// Functions: rmnLn(char *)
// Description: Removes newline from string
void rmnLn(char *string) {
    int i;
    for (i = 0; i < strlen(string); i++) {
        if (string[i] == '\n') {
            string[i] = '\0';
        }
    }
}

// Function: read_command_file
// Description: Reads the command from crontab-file and stores it in an array
void read_crontab_file() 
{
    dict = fopen(crontab_file, "r");
    // print Error if file does not exist
    if (dict == NULL) {
        printf("Error: File not found.\n");
        exit(EXIT_FAILURE);
    }

    // malloc the cron_line array
    cron_line = malloc(MAX_LINE_SIZE * sizeof(char));

    // read the file line by line
    i = 0;
    while( fgets(cron_line, MAX_LINE_SIZE, dict) != NULL ) {
        //if command start with "#" then skip it
        if (cron_line[0] == '#') {
            continue;
        }
        rmnLn(cron_line);
        strcpy(cron_command[i], cron_line);
        total_cron_lines++;
        i++;
    }
    fclose(dict);
}

// Function: read_estimates_file
// Description: Reads the estimates from estimates-file and append the estimates time behind the same command
void read_estimates_file() 
{
    dict = fopen(estimates_file, "r");
    // print Error if file does not exist
    if (dict == NULL) {
        printf("Error: File not found.\n");
        exit(EXIT_FAILURE);
    }

    command = malloc(MAX_LINE_SIZE * sizeof(char));
    estimate_line = malloc(MAX_LINE_SIZE * sizeof(char));
    count_list = malloc(total_cron_lines * sizeof(int));

    // read the file line by line
    while( fgets(estimate_line, MAX_LINE_SIZE, dict) != NULL ) {
        //if command start with "#" then skip it
        if (estimate_line[0] == '#') {
            continue;
        }

        // get the command from the estimate_line
        char *command = strtok(estimate_line, " ");
        char *estimateTime = strtok(NULL, " ");
        rmnLn(estimateTime);
        i = 0;
        while (!strext(cron_command[i], command)) {
            i++;
        }
        strcat(cron_command[i], "   ");
        strcat(cron_command[i], estimateTime);
        count_list[i] = 1;
    }
    fclose(dict);
}

// Function: check_cron_list
// Description: Checks if every command have estimate time
void check_cron_list(){
    for (i = 0; i < total_cron_lines; i++) {
        if (count_list[i] != 1) {
            char *cpyline;
            strcpy(cpyline, cron_command[i]);
            command = strtok(cpyline, " "); 
            command = strtok(NULL, " ");
            command = strtok(NULL, " ");
            command = strtok(NULL, " ");
            command = strtok(NULL, " ");
            command = strtok(NULL, " ");
            printf("Error: Command \"%s\" does not have estimate time.\n", command);
            exit(EXIT_FAILURE);
        }
    }
}

int main(int argc, char* argv[]) 
{
    // check if the number of arguments is correct
    // read the arguments if correct, otherwise print error
    if (argc != 4) {
        printf("Error: Wrong number of arguments.\n");
        exit(EXIT_FAILURE);
    }
    month = atoi(argv[1]);
    crontab_file = argv[2];
    estimates_file = argv[3];
    cron_command = malloc(MAX_LIST_SIZE * sizeof(char*));
    for (i = 0; i < MAX_LIST_SIZE; i++) {
        cron_command[i] = malloc(MAX_COMMAND_SIZE * sizeof(char));
    }

    // read the crontab-file
    read_crontab_file(cron_command);
    // read the estimates-file
    read_estimates_file(cron_command);
    // check if the estimates are valid
    check_cron_list(cron_command);
    // print the cron commands
    int testlist[total_cron_lines];
    for (i = 0; i < total_cron_lines; i++) {
        printf("%i: %s\n", i, cron_command[i]);;
    }
    return 0;
}