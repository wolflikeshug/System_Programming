//  CITS2002 Project 1 2022
//  Student1:   23006364   Hu   Daniel

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LIST_SIZE 21
#define MAX_LINE_SIZE 101
#define MAX_COMMAND_SIZE 41
#define VALID_MINUTES_LIST_SIZE 61
#define VALID_MINUTES 60
#define VALID_HOURS_LIST_SIZE 25
#define VALID_HOURS 24
#define VALID_DATE_LIST_SIZE 32
#define VALID_MONTHS_LIST_SIZE 13
#define VALID_MONTHS 12
#define VALID_DAY_LIST_SIZE 15
#define VALID_DAYS 7

typedef struct crontab_line
{
    char cmd[MAX_COMMAND_SIZE]; // command to run
    int sch_minute;             // schedule for the process
    int sch_hour;
    int sch_date;
    int sch_month;
    int sch_day_of_week;
    int est; // estimates time for each command
} crontab_line;

typedef struct time_struct
{
    int minute;
    int hour;
    int date;
    int month;
    int day_of_week;
} time_struct;

typedef struct record_pad
{
    char cmd[MAX_COMMAND_SIZE]; // command name
    int time;                   // total period runs for the commandnot-set

} record_pad;

FILE *dict;

int month;
int total_cron_lines;
int *count_list;
int curr_year = 2022;
int days_in_month[VALID_MONTHS_LIST_SIZE] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
char *crontab_file;
char *estimates_file;
char *valid_minute[] = {"*", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59"};
char *valid_hour[] = {"*", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23"};
char *valid_date[] = {"*", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31"};
char *valid_month[] = {"*", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"};
char *valid_day_of_week[] = {"*", "0", "1", "2", "3", "4", "5", "6", "mon", "tue", "wed", "thu", "fri", "sat", "sun"};
crontab_line cron_command[MAX_LIST_SIZE];

// Fuction: strext(char *, char *)
// Description: Returns True if string2 is contained in string1
bool strext(char *string1, char *string2)
{
    for (int i = 0; i < strlen(string1); i++)
    {
        if (string1[i] == string2[0])
        {
            if (strncmp(string1 + i, string2, strlen(string2)) == 0)
            {
                return true;
            }
        }
    }
    return false;
}

// Function: rmnLn(char *)
// Description: Removes newline from string
void rmnLn(char *string)
{
    for (int i = 0; i < strlen(string); i++)
    {
        if (string[i] == '\n')
        {
            string[i] = '\0';
        }
    }
}

// Functions: charInList(char *, char **)
// Description: Returns True if char is in list
bool charInList(char *char1, char *list[])
{
    for (int i = 0; i < MAX_LIST_SIZE; i++)
    {
        if (strcmp(char1, list[i]) == 0)
        {
            return true;
        }
    }
    return false;
}

// Funcion: chgTimeFomat(char *)
// Description: Changes minutes format from char to int, if char is *, returns -1
int chgTimeFomat(char *char1)
{
    if (strcmp(char1, "*") == 0)
    {
        return -1;
    }
    return atoi(char1);
}

// Funcion: chgDayFomat(char *)
// Description: Changes day format from mon-sun to 0-6, if char is *, returns -1
int chgDayFomat(char *day)
{
    if (strext(day, "mon"))
    {
        return 0;
    }
    else if (strext(day, "tue"))
    {
        return 1;
    }
    else if (strext(day, "wed"))
    {
        return 2;
    }
    else if (strext(day, "thu"))
    {
        return 3;
    }
    else if (strext(day, "fri"))
    {
        return 4;
    }
    else if (strext(day, "sat"))
    {
        return 5;
    }
    else if (strext(day, "sun"))
    {
        return 6;
    }
    else if (strext(day, "*"))
    {
        return -1;
    }
    return atoi(day);
}

// Function: getDayOfWeek(int, int, int)
// Description: Returns the week day of week for given date
int getDayOfWeek(int month, int date, int year)
{
    int day = 0;
    int year_temp = year - (14 - month) / 12;
    int x = year_temp + year_temp / 4 - year_temp / 100 + year_temp / 400;
    int month_temp = month + 12 * ((14 - month) / 12) - 2;
    day = (date + x + 31 * month_temp / 12) % 7;
    return day;
}

// Function: getDaysInMonth(int)
// Description: Returns the number of days in month
int getDaysInMonth(int month)
{
    return days_in_month[month];
}

// Function: ckState(time_struct, time_struct, int)
// Description: Returns true if the number of minutes between two times greater than estimate minutes, if time1 is greater than time2, returns false
bool ckState(time_struct time1, time_struct time2, int estimate_minutes)
{
    // turn times points into how many minutes after the start of the month
    int minutes_start = time1.minute + time1.hour * VALID_MINUTES + time1.date * VALID_HOURS * VALID_MINUTES;
    int minutes_now = time2.minute + time2.hour * VALID_MINUTES + time2.date * VALID_HOURS * VALID_MINUTES;
    int minutes_between = minutes_now - minutes_start; // cal the number of minutes from time command start to now
    if (minutes_between > estimate_minutes)
    {
        return true;
    }
    return false;
}

// Function: whenToRun(time_struct)


// Functions: precheck(char *)
// Description: precheck the file if all the lines are less than 100 characters ( not including \n haracter)
void precheck(char *file)
{
    FILE *fp = fopen(file, "r");
    if (fp == NULL)
    {
        printf("Error: File not found.\n");
        exit(EXIT_FAILURE);
    }
    int count = 0;
    while (!feof(fp))
    {
        char tmp;
        tmp = fgetc(fp);
        count++;
        if (count > MAX_LINE_SIZE)
        {
            fclose(fp);
            printf("Error: File contain oversize line.\n");
            exit(EXIT_FAILURE);
        }
        if (tmp == '\n')
        {
            count = 0;
        }
    }
    fclose(fp);
}

// Function: check_cron_format
// Description: Checks if cron's schedule is in correct format
void check_cron_format(char *cronLn)
{

    char *cpyLn = malloc(sizeof(char) * MAX_LINE_SIZE); // malloc space for cpyLn
    strcpy(cpyLn, cronLn);

    strtok(cpyLn, " "); // check the format
    for (int i = 0; i < 5; i++)
    { // run 7 times (include above line), there should be excately 6 elements in the line
        char *tmp = strtok(NULL, " ");
        if (i <= 4 && tmp == NULL)
        {
            printf("Error: Wrong format for cron schedule.\n"); // if there is less than 6 element, wrong format
            exit(EXIT_FAILURE);
        }
        else if (i > 4 && tmp != NULL)
        {
            printf("Error: Wrong format for cron schedule.\n"); // if there is more than 6 element, wrong format
            exit(EXIT_FAILURE);
        }
        else if (i == 4 && strlen(tmp) > MAX_COMMAND_SIZE)
        {
            printf("Error: Too long for cron command.\n"); // if coomand is more than 41 characters, wrong format
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

    for (int i = 0; i < VALID_MINUTES_LIST_SIZE; i++)
    {
        if (!bool1 && i < VALID_MINUTES_LIST_SIZE && strcmp(char1, valid_minute[i]) == 0)
        {
            bool1 = true;
        }
        if (!bool2 && i < VALID_HOURS_LIST_SIZE && strcmp(char2, valid_hour[i]) == 0)
        {
            bool2 = true;
        }
        if (!bool3 && i < VALID_DATE_LIST_SIZE && strcmp(char3, valid_date[i]) == 0)
        {
            bool3 = true;
        }
        if (!bool4 && i < VALID_MONTHS_LIST_SIZE && strcmp(char4, valid_month[i]) == 0)
        {
            bool4 = true;
        }
        if (!bool5 && i < VALID_DAY_LIST_SIZE && strcmp(char5, valid_day_of_week[i]) == 0)
        {
            bool5 = true;
        }
        if (bool1 && bool2 && bool3 && bool4 && bool5)
        {
            free(cpyLn);
            return;
        }
    }
    free(cpyLn);                                        // free memory
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
    if (dict == NULL)
    {
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
    while (fgets(cron_line, MAX_LINE_SIZE, dict) != NULL)
    {
        // if command start with "#" then skip it
        if (cron_line[0] == '#')
        {
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
        cron_command[i].sch_minute = chgTimeFomat(minutes);
        cron_command[i].sch_hour = chgTimeFomat(hours);
        cron_command[i].sch_date = chgTimeFomat(date);
        cron_command[i].sch_month = chgTimeFomat(month);
        cron_command[i].sch_day_of_week = chgDayFomat(day_of_week);

        total_cron_lines++;
        i++;
    }
    free(cron_line);
    fclose(dict);
}

// Function: check_estimate_format(char *)
// Description: Checks if the estimate is in correct format
void check_estimate_format(char *estimate)
{
    char *cpyEstimate = malloc(sizeof(char) * MAX_LINE_SIZE); // malloc space for cpyEstimate
    strcpy(cpyEstimate, estimate);
    char *tmp = strtok(cpyEstimate, " "); // check the format
    for (int i = 0; i < 4; i++)
    { // run 2 times (include above line), there should be excately 2 element in the line
        if (i < 2 && tmp == NULL)
        {
            printf("Error: Wrong format for estimate.\n"); // if there is less than 2 element, there is wrong format
            exit(EXIT_FAILURE);
        }
        else if (i >= 2 && tmp != NULL)
        {
            printf("Error: Wrong format for estimate.\n"); // if there is more than 2 element, there is wrong format
            exit(EXIT_FAILURE);
        }
        else if (i == 0 && strlen(tmp) > MAX_COMMAND_SIZE)
        {
            printf("Error: Too long for estimate command.\n"); // if command is more than 41 characters, there is wrong format
            exit(EXIT_FAILURE);
        }
        else if (i == 1 && atoi(tmp) <= 0)
        {
            printf("Error: Wrong  time estimation.\n"); // the second element should be positive integer
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
    if (dict == NULL)
    {
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
    while (fgets(estimate_line, MAX_LINE_SIZE, dict) != NULL)
    {

        // if command start with "#" then skip it
        if (estimate_line[0] == '#')
        {
            continue;
        }

        check_estimate_format(estimate_line); // check the format
        // get the command from the estimate_line
        char *command = strtok(estimate_line, " ");
        char *estimateTime = strtok(NULL, " ");
        rmnLn(estimateTime);
        int i = 0;
        while (!strext(cron_command[i].cmd, command))
        {
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
void check_cron_list()
{
    for (int i = 0; i < total_cron_lines; i++)
    {
        if (count_list[i] != 1)
        {
            printf("Error: Command \"%s\" cannot find right estimate time.\n", cron_command[i].cmd);
            exit(EXIT_FAILURE);
        }
    }
}

// Function: ckComState(crontab_line *, int, int, int)
// Description: Checks if the command is running or not at the given time
bool ckComState(crontab_line cron_command, int curr_minute, int curr_hour, int curr_date, int curr_day)
{

}

// Function: time_simulator(int)
// Description: This function simulates the siquation of every minute in the target month
// and record the data we interested in (we assume that the target month is in the current year),
// and return the array of the data we interested in.
int *time_simulator(int month)
{
    time_struct tm;
    tm.month = month;
    for (tm.date = 0; tm.date < days_in_month[tm.month]; tm.date++)
    {
        for (tm.hour = 0; tm.hour < 24; tm.hour++)
        {
            for (tm.minute = 0; tm.minute < 60; tm.minute++)
            {
                return NULL;
            }
        }
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    // check if the number of arguments is correct
    // read the arguments if correct, otherwise print error
    if (argc != 4)
    {
        // printf("Error: Wrong number of arguments.\n");
        // exit(EXIT_FAILURE);
        month = 2;
        crontab_file = "crontab-file";
        estimates_file = "estimate-file";
    }
    else
    {
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
    for (int i = 0; i < total_cron_lines; i++)
    {
        printf("%i: %i\t%i\t%i\t%i\t%i\t%i\t%s\n", i,
               cron_command[i].sch_minute,
               cron_command[i].sch_hour,
               cron_command[i].sch_date,
               cron_command[i].sch_month,
               cron_command[i].sch_day_of_week,
               cron_command[i].est,
               cron_command[i].cmd);
        ;
    }
    return 0;
}