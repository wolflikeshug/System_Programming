#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LIST_SIZE 21
#define MAX_LINE_SIZE 101
#define MAX_COMMAND_SIZE 41
#define VALID_MINUTES 61
#define VALID_HOURS 25
#define VALID_DATE 32
#define VALID_MONTHS 13
#define VALID_DAY 15

int month;
char *crontab_file;
char *estimates_file;
char *valid_minutes[] = {"*","0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58","59"};
char *valid_hour[] = {"*","0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23"};
char *valid_date[] = {"*","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31"};
char *valid_month[] = {"*","0","1","2","3","4","5","6","7","8","9","10","11"};
char *valid_day_of_week[] = {"*","0","1","2","3","4","5","6","mon","tue","wed","thu","fri","sat","sun"};

FILE *dict;

int total_cron_lines;
int *count_list;
char *command;
char *cron_line;
char *estimate_line;
char **cron_command;

// Fuctions: strext(char *, char *)
// Description: Returns True if string2 contained in string1
bool strext(char *string1, char *string2) {
    for (int i = 0; i < strlen(string1); i++) {
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
    for (int i = 0; i < strlen(string); i++) {
        if (string[i] == '\n') {
            string[i] = '\0';
        }
    }
}

// Functions: charInList(char *, char **)
// Description: Returns True if char is in list
bool charInList(char *char1, char *list[]) {
    for (int i = 0; i < MAX_LIST_SIZE; i++) {
        if (strext(char1, list[i])) {
            return true;
        }
    }
    return false;
}

// Function: check_cron_list
// Description: Checks if every command have estimate time
void check_cron_list(){
    // malloc memory for cpyLn
    char *cpyLn = (char *)malloc(sizeof(char) * MAX_LINE_SIZE);

    for (int i = 0; i < total_cron_lines; i++) {
        if (count_list[i] != 1) {
            strcpy(cpyLn, cron_command[i]);
            command = strtok(cpyLn, " "); 
            command = strtok(NULL, " ");
            command = strtok(NULL, " ");
            command = strtok(NULL, " ");
            command = strtok(NULL, " ");
            command = strtok(NULL, " ");
            printf("Error: Command \"%s\" does not have estimate time.\n", command);
            exit(EXIT_FAILURE);
        }
    }
    free(cpyLn);
}

// Function: check_cron_format
// Description: Checks if cron's schedule is in correct format
bool check_cron_format(char* cronLn){
    // malloc space for cpyLn
    char *cpyLn = malloc(sizeof(char) * MAX_LINE_SIZE);

    strcpy(cpyLn, cronLn);
    char *char1 = strtok(cpyLn, " ");
    char *char2 = strtok(NULL, " ");
    char *char3 = strtok(NULL, " ");
    char *char4 = strtok(NULL, " ");
    char *char5 = strtok(NULL, " ");

    bool bool1 = false;
    bool bool2 = false;
    bool bool3 = false;
    bool bool4 = false;
    bool bool5 = false;

    for (int i = 0; i < VALID_MINUTES; i++) {
        if (!bool1 && i < VALID_MINUTES && strcmp(char1, valid_minutes[i]) == 0) {
            bool1 = true;
        }
        if (!bool2 && i < VALID_HOURS && strcmp(char2, valid_hour[i]) == 0) {
            bool2 = true;
        }
        if (!bool3 && i < VALID_DATE && strcmp(char3, valid_date[i]) == 0) {
            bool3 = true;
        }
        if (!bool4 && i < VALID_MONTHS && strcmp(char4, valid_month[i]) == 0) {
            bool4 = true;
        }
        if (!bool5 && i < VALID_DAY && strcmp(char5, valid_day_of_week[i]) == 0) {
            bool5 = true;
        }
        if (bool1 && bool2 && bool3 && bool4 && bool5) {
            free(cpyLn);
            return true;
        }
    }
    free(cpyLn);
    return false;
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
    int i = 0;
    while( fgets(cron_line, MAX_LINE_SIZE, dict) != NULL ) {
        //if command start with "#" then skip it
        if (cron_line[0] == '#') {
            continue;
        }

        // if the formate of cron is not valid then exit with error
        if (!check_cron_format(cron_line)) {
            printf("Error: Invalid cron format.\n");
            exit(EXIT_FAILURE);
        }

        rmnLn(cron_line);
        strcpy(cron_command[i], cron_line);
        total_cron_lines++;
        i++;
    }
    free(cron_line);
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
        int i = 0;
        while (!strext(cron_command[i], command)) {
            i++;
        }
        strcat(cron_command[i], "   ");
        strcat(cron_command[i], estimateTime);
        count_list[i] = 1;
    }
    free(command);
    free(estimate_line);
    fclose(dict);
}


int main(int argc, char* argv[]) 
{
    // check if the number of arguments is correct
    // read the arguments if correct, otherwise print error
    if (argc != 4) {
        //printf("Error: Wrong number of arguments.\n");
        //exit(EXIT_FAILURE);
        month = 2;
        crontab_file = "crontab-file";
        estimates_file = "estimate-file";
    }
    else{
        month = atoi(argv[1]);
        crontab_file = argv[2];
        estimates_file = argv[3];
    }

    cron_command = malloc(MAX_LIST_SIZE * MAX_COMMAND_SIZE * sizeof(char*));
    for (int i = 0; i < MAX_LIST_SIZE; i++) {
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
    for (int i = 0; i < total_cron_lines; i++) {
        printf("%i: %s\n", i, cron_command[i]);;
    }
    return 0;
}