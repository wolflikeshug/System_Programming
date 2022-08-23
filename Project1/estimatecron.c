#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LIST_SIZE 21
#define MAX_LINE_SIZE 101
#define MAX_COMMAND_SIZE 41
#define MAX_TIME_SIZE 3
#define VALID_MINUTES 61
#define VALID_HOURS 25
#define VALID_DATE 32
#define VALID_MONTHS 13
#define VALID_DAY 15

typedef struct crontab_line {
    char        cmd[MAX_COMMAND_SIZE];      // command to run
    char        sch_minute[MAX_TIME_SIZE];      // schedule for the process
    char        sch_hour[MAX_TIME_SIZE];
    char        sch_date[MAX_TIME_SIZE];
    char        sch_month[MAX_TIME_SIZE];
    char        sch_day_of_week[MAX_TIME_SIZE];
    int         est;                        //estimates time for each command
} crontab_line; 

FILE *dict;

int month;
int total_cron_lines;
int *count_list;
char *crontab_file;
char *estimates_file;
char *valid_minutes[] = {"*","0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58","59"};
char *valid_hour[] = {"*","0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23"};
char *valid_date[] = {"*","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31"};
char *valid_month[] = {"*","0","1","2","3","4","5","6","7","8","9","10","11"};
char *valid_day_of_week[] = {"*","0","1","2","3","4","5","6","mon","tue","wed","thu","fri","sat","sun"};
crontab_line cron_command[MAX_LIST_SIZE];

// Oh My, Look at this. I really need a header file, this c file looks way too long.

// Fuctions: strext(char *, char *)
// Description: Returns True if string2 is contained in string1
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
        if (strcmp(char1, list[i]) == 0) {
            return true;
        }
    }
    return false;
}

// Funcions: chgDayFomat(char *)
// Description: Changes day format from mon-sun to 0-6
char *chgDayFomat(char *day) {
    if (strext(day, "mon")) {
        return "0";
    } else if (strext(day, "tue")) {
        return "1";
    } else if (strext(day, "wed")) {
        return "2";
    } else if (strext(day, "thu")) {
        return "3";
    } else if (strext(day, "fri")) {
        return "4";
    } else if (strext(day, "sat")) {
        return "5";
    } else if (strext(day, "sun")) {
        return "6";
    }
    return day;
}

// Functions: precheck(char *)
// Description: precheck the file if all the lines are less than 100 characters ( not including \n haracter)
void precheck(char *file) {
    FILE *fp = fopen(file, "r");
    if (fp == NULL) {
        printf("Error: File not found.\n");
        exit(EXIT_FAILURE);
    }
    int count = 0;
    while (!feof(fp)) {
        char tmp;
        tmp = fgetc(fp);
        count++;
        if (count > MAX_LINE_SIZE) {
            fclose(fp);
            printf("Error: File contain oversize line.\n");
            exit(EXIT_FAILURE);
        }
        if (tmp == '\n') {
            count = 0;
        }
    }
    fclose(fp);
}

// Function: check_cron_format
// Description: Checks if cron's schedule is in correct format
void check_cron_format(char* cronLn){

    char *cpyLn = malloc(sizeof(char) * MAX_LINE_SIZE); // malloc space for cpyLn
    strcpy(cpyLn, cronLn);

    strtok(cpyLn, " "); // check the format
    for(int i = 0; i < 5; i++){ // run 7 times (include above line), there should be excately 6 elements in the line
        char *tmp = strtok(NULL, " ");
        if(i <= 4 && tmp == NULL){
            printf("Error: Wrong format for cron schedule.\n");// if there is less than 6 element, wrong format
            exit(EXIT_FAILURE);
        }
        else if(i > 4 && tmp != NULL){
            printf("Error: Wrong format for cron schedule.\n");// if there is more than 6 element, wrong format
            exit(EXIT_FAILURE);
        }
        else if (i == 4 && strlen(tmp) > MAX_COMMAND_SIZE){
            printf("Error: Too long for cron command.\n");// if coomand is more than 41 characters, wrong format
            exit(EXIT_FAILURE);
        }
    }

    strcpy(cpyLn, cronLn);
    char *char1 = strtok(cpyLn, " ");
    char *char2 = strtok(NULL, " ");
    char *char3 = strtok(NULL, " ");
    char *char4 = strtok(NULL, " ");
    char *char5 = strtok(NULL, " ");

    bool bool1 = false; // if the formate is correct, bool will be true
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
            return;
        }
    }
    free(cpyLn); // free memory
    printf("Error: Wrong format for cron schedule.\n"); // if there is no match, there is wrong format
    exit(EXIT_FAILURE);
}

// Function: read_command_file
// Description: Reads the command from crontab-file and stores it in an array
void read_crontab_file() 
{
    char *cron_line;
    dict = fopen(crontab_file, "r");
    // print Error if file does not exist
    if (dict == NULL) {
        printf("Error: Crontab-File cannot be found.\n");
        printf("This Error can be caused by the following reasons:\n");
        printf("1. The file does not exist.\n");
        printf("2. The file is empty.\n");
        printf("3. Do not have premission to access the file.\n");
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
        check_cron_format(cron_line);

        rmnLn(cron_line);
        char *minutes = strtok(cron_line, " ");
        char *hours = strtok(NULL, " ");
        char *date = strtok(NULL, " ");
        char *month = strtok(NULL, " ");
        char *day_of_week = strtok(NULL, " ");
        char *command = strtok(NULL, " ");

        strcpy(cron_command[i].cmd, command);
        strcpy(cron_command[i].sch_minute,      minutes);
        strcpy(cron_command[i].sch_hour,        hours);
        strcpy(cron_command[i].sch_date,        date);
        strcpy(cron_command[i].sch_month,       month);
        strcpy(cron_command[i].sch_day_of_week, chgDayFomat(day_of_week));

        total_cron_lines++;
        i++;
    }
    free(cron_line);
    fclose(dict);
}

// Function: check_estimate_format(char *)
// Description: Checks if the estimate is in correct format
void check_estimate_format(char *estimate) {
    char *cpyEstimate = malloc(sizeof(char) * MAX_LINE_SIZE); // malloc space for cpyEstimate
    strcpy(cpyEstimate, estimate);
    char *tmp = strtok(cpyEstimate, " "); // check the format
    for(int i = 0; i < 4; i++){ //run 2 times (include above line), there should be excately 2 element in the line
        if(i < 2 && tmp == NULL){
            printf("Error: Wrong format for estimate.\n");  // if there is less than 2 element, there is wrong format
            exit(EXIT_FAILURE);
        }
        else if(i >= 2 && tmp != NULL){
            printf("Error: Wrong format for estimate.\n");  // if there is more than 2 element, there is wrong format
            exit(EXIT_FAILURE);
        }
        else if(i == 0 && strlen(tmp) > MAX_COMMAND_SIZE){
            printf("Error: Too long for estimate command.\n");  // if command is more than 41 characters, there is wrong format
            exit(EXIT_FAILURE);
        }
        else if(i == 1 && atoi(tmp) <= 0){
            printf("Error: Wrong  time estimation.\n");  // the second element should be positive integer
            exit(EXIT_FAILURE);
        }
        tmp = strtok(NULL, " ");
    }
    free(cpyEstimate); // free memory
}

// Function: read_estimates_file
// Description: Reads the estimates from estimates-file and append the estimates time behind the same command
void read_estimates_file() 
{
    char *command;
    char *estimate_line;
    dict = fopen(estimates_file, "r");
    // print Error if file does not exist
    if (dict == NULL) {
        printf("Error: Estimates-File cannot be found.\n");
        printf("This Error can be caused by the following reasons:\n");
        printf("1. The file does not exist.\n");
        printf("2. The file is empty.\n");
        printf("3. Do not have premission to access the file.\n");
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

        check_estimate_format(estimate_line); // check the format
        // get the command from the estimate_line
        char *command = strtok(estimate_line, " ");
        char *estimateTime = strtok(NULL, " ");
        rmnLn(estimateTime);
        int i = 0;
        while (!strext(cron_command[i].cmd, command)) {
            i++;
        }
        cron_command[i].est = atoi(estimateTime);
        count_list[i] = 1;
    }
    free(command);
    free(estimate_line);
    fclose(dict);
}

// Function: check_cron_list
// Description: Checks if every command have estimate time
void check_cron_list(){
    for (int i = 0; i < total_cron_lines; i++) {
        if (count_list[i] != 1) {
            printf("Error: Command \"%s\" cannot find right estimate time.\n", cron_command[i].cmd);
            exit(EXIT_FAILURE);
        }
    }
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

    // precheck the crontab-file and estimate-file
    precheck(crontab_file);
    precheck(estimates_file);

    // read the crontab-file and estimates-file
    read_crontab_file();
    read_estimates_file();

    // check if the estimates are valid
    check_cron_list();

    // print the cron commands
    int testlist[total_cron_lines];
    printf("minute\thour\tdate\tmonth\tDOW\test\tcommand\n");
    for (int i = 0; i < total_cron_lines; i++) {
        printf("%i: %s\t%s\t%s\t%s\t%s\t%i\t%s\n", i, \
        cron_command[i].sch_minute,\
        cron_command[i].sch_hour,\
        cron_command[i].sch_date,\
        cron_command[i].sch_month,\
        cron_command[i].sch_day_of_week,\
        cron_command[i].est,\
        cron_command[i].cmd);;
    }
    return 0;
}