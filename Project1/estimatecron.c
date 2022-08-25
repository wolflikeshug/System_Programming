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
#define VALID_MONTHS_LIST_SIZE 25
#define VALID_MONTHS 12
#define VALID_DAY_LIST_SIZE 15
#define VALID_DAYS 7

typedef struct crontab_line
{
    char cmd[MAX_COMMAND_SIZE];                 // command to run
    int sch_minute;                             // schedule for the process
    int sch_hour;
    int sch_date;
    int sch_month;
    int sch_day_of_week;
    int est;                                    // estimates time for each command
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
    crontab_line    command;                    // command
    bool            state;                      // true if the command is active, false if not
    int             remaining_minutes;          // time left for the command to end
    int             time;                       // total period runs for the commandnot-set

} record_pad;

FILE *dict;

int month;
int total_cron_lines;
int *count_list;
int curr_year = 2022;
int proccess_count = 0;
int days_in_month[VALID_MONTHS_LIST_SIZE] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
char *crontab_file;
char *estimates_file;
char *valid_minute[] = {"*", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59"};
char *valid_hour[] = {"*", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23"};
char *valid_date[] = {"*", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31"};
char *valid_month[] = {"*", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"};
char *valid_day_of_week[] = {"*", "0", "1", "2", "3", "4", "5", "6", "mon", "tue", "wed", "thu", "fri", "sat", "sun"};
record_pad *cron_command;

// =====================================================================================
//                                  TOOL FUNCTIONS
// =====================================================================================

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
// Description: Changes day format from sun-sat to 0-6, if char is *, returns -1
int chgDayFomat(char *day)
{
    if (strcmp(day, "*") == 0)
    {
        return -1;
    }
    else if (strcmp(day, "sun") == 0)
    {
        return 0;
    }
    else if (strcmp(day, "mon") == 0)
    {
        return 1;
    }
    else if (strcmp(day, "tue") == 0)
    {
        return 2;
    }
    else if (strcmp(day, "wed") == 0)
    {
        return 3;
    }
    else if (strcmp(day, "thu") == 0)
    {
        return 4;
    }
    else if (strcmp(day, "fri") == 0)
    {
        return 5;
    }
    else if (strcmp(day, "sat") == 0)
    {
        return 6;
    }
    return atoi(day);
}

// Function: chgMonthFomat(char *)
// Description: Changes month format from jan,feb,etc to 0-11, if char is *, returns -1
int chgMonthFomat(char *month)
{
    if (strcmp(month, "*") == 0)
    {
        return -1;
    }
    else if (strcmp(month, "jan") == 0)
    {
        return 0;
    }
    else if (strcmp(month, "feb") == 0)
    {
        return 1;
    }
    else if (strcmp(month, "mar") == 0)
    {
        return 2;
    }
    else if (strcmp(month, "apr") == 0)
    {
        return 3;
    }
    else if (strcmp(month, "may") == 0)
    {
        return 4;
    }
    else if (strcmp(month, "jun") == 0)
    {
        return 5;
    }
    else if (strcmp(month, "jul") == 0)
    {
        return 6;
    }
    else if (strcmp(month, "aug") == 0)
    {
        return 7;
    }
    else if (strcmp(month, "sep") == 0)
    {
        return 8;
    }
    else if (strcmp(month, "oct") == 0)
    {
        return 9;
    }
    else if (strcmp(month, "nov") == 0)
    {
        return 10;
    }
    else if (strcmp(month, "dec") == 0)
    {
        return 11;
    }
    return atoi(month);
}

// Function: getDayOfWeek(int, int, int)
// Description: Returns the week day of week for given date
int getDayOfWeek(int month, int date)
{
    int day = 0;
    int year = curr_year;
    month += 1;
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

// Function: isitTime(int, int)
// Description: Returns True if two int is same, or if int1 is -1 (all)
bool isitTime(int int1, int int2)
{
    if (int1 == int2 || int1 == -1)
    {
        return true;
    }
    return false;
}

// Function: chgDayFomatReverse(int)
// Description: Changes day format from 0-6 to sun-sat
char *chgDayFomatReverse(int day)
{
    if (day == 0)
    {
        return "sun";
    }
    else if (day == 1)
    {
        return "mon";
    }
    else if (day == 2)
    {
        return "tue";
    }
    else if (day == 3)
    {
        return "wed";
    }
    else if (day == 4)
    {
        return "thu";
    }
    else if (day == 5)
    {
        return "fri";
    }
    else if (day == 6)
    {
        return "sat";
    }
    return "";
}

// Function: chgMonthFomatReverse(int)
// Description: Changes month format from 0-11 to Jan,Feb,etc
char *chgMonthFomatReverse(int month)
{
    if (month == 0)
    {
        return "Jan";
    }
    else if (month == 1)
    {
        return "Feb";
    }
    else if (month == 2)
    {
        return "Mar";
    }
    else if (month == 3)
    {
        return "Apr";
    }
    else if (month == 4)
    {
        return "May";
    }
    else if (month == 5)
    {
        return "Jun";
    }
    else if (month == 6)
    {
        return "Jul";
    }
    else if (month == 7)
    {
        return "Aug";
    }
    else if (month == 8)
    {
        return "Sep";
    }
    else if (month == 9)
    {
        return "Oct";
    }
    else if (month == 10)
    {
        return "Nov";
    }
    else if (month == 11)
    {
        return "Dec";
    }
    return "";
}

// Function: findChamp()
// Description: Go throught cron_command and return the cron have highest time
record_pad findchamp()
{
    record_pad champ = cron_command[0];
    for (int i = 1; i < total_cron_lines; i++)
    {
        if (champ.time < cron_command[i].time)
        {
            champ = cron_command[i];
        }
    }
    return champ;
}

// =====================================================================================
//                                  CRON FUNCTIONS
// =====================================================================================

// Functions: precheck(char *)
// Description: precheck the file if all the lines are less than 100 characters ( not including \n haracter)
void precheck(char *file)
{
    FILE *fp = fopen(file, "r");
    if (fp == NULL)
    {
        printf("Error: \"%s\" not found.\n", file);
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
            printf("Error: Wrong format for cron schedule.\n");     // if there is less than 6 element, wrong format
            exit(EXIT_FAILURE);
        }
        else if (i > 4 && tmp != NULL)
        {
            printf("Error: Wrong format for cron schedule.\n");     // if there is more than 6 element, wrong format
            exit(EXIT_FAILURE);
        }
        else if (i == 4 && strlen(tmp) > MAX_COMMAND_SIZE)
        {
            printf("Error: Too long for cron command.\n");          // if coomand is more than 41 characters, wrong format
            exit(EXIT_FAILURE);
        }
    }

    strcpy(cpyLn, cronLn);
    char *char1 = strtok(cpyLn, " ");
    char *char2 = strtok(NULL, " ");
    char *char3 = strtok(NULL, " ");
    char *char4 = strtok(NULL, " ");
    char *char5 = strtok(NULL, " ");
    char *char6 = strtok(NULL, " ");
    char *char7 = strtok(NULL, " ");

    bool bool1 = false;                                             // if the formate is correct, bool will be true
    bool bool2 = false;
    bool bool3 = false;
    bool bool4 = false;
    bool bool5 = false;

    if (strlen(char6) > 40)
    {
        printf("Error: Too long for cron command.\n");
        exit(EXIT_FAILURE);
    }
    if (char7 != NULL)
    {
        printf("Error: Too many argument.\n");
        exit(EXIT_FAILURE);
    }

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
    free(cpyLn);                                                        // free memory
    printf("Error: Wrong format for cron schedule.\n");
    exit(EXIT_FAILURE);
}

// Function: read_command_file
// Description: Reads the command from crontab-file and stores it in an array
void read_crontab_file()
{
    char *cron_line;
    dict = fopen(crontab_file, "r");
    cron_line = malloc(MAX_LINE_SIZE * sizeof(char));                   // malloc the cron_line array

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

        // set up the cron_line array
        strcpy(cron_command[i].command.cmd, command);
        cron_command[i].command.sch_minute = chgTimeFomat(minutes);
        cron_command[i].command.sch_hour = chgTimeFomat(hours);
        cron_command[i].command.sch_date = chgTimeFomat(date);
        cron_command[i].command.sch_month = chgMonthFomat(month);
        cron_command[i].command.sch_day_of_week = chgDayFomat(day_of_week);
        cron_command[i].state = false;
        cron_command[i].remaining_minutes = 0;
        cron_command[i].time = 0;

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
    char *cpyEstimate = malloc(sizeof(char) * MAX_LINE_SIZE);           // malloc space for cpyEstimate
    strcpy(cpyEstimate, estimate);
    char *tmp = strtok(cpyEstimate, " "); // check the format
    for (int i = 0; i < 4; i++)                                         // run 2 times (include above line), there should be excately 2 element in the line
    {                          
        if (i < 2 && tmp == NULL)
        {
            printf("Error: Wrong format for estimate.\n");              // if there is less than 2 element, there is wrong format
            exit(EXIT_FAILURE);
        }
        else if (i >= 2 && tmp != NULL)
        {
            printf("Error: Wrong format for estimate.\n");              // if there is more than 2 element, there is wrong format
            exit(EXIT_FAILURE);
        }
        else if (i == 0 && strlen(tmp) > MAX_COMMAND_SIZE)
        {
            printf("Error: Too long for estimate command.\n");          // if command is more than 41 characters, there is wrong format
            exit(EXIT_FAILURE);
        }
        else if (i == 1 && atoi(tmp) <= 0)
        {
            printf("Error: Wrong  time estimation.\n");                 // the second element should be positive integer
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

    command = malloc(MAX_LINE_SIZE * sizeof(char));
    estimate_line = malloc(MAX_LINE_SIZE * sizeof(char));
    
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
        while (!strext(cron_command[i].command.cmd, command))
        {
            i++;
        }
        cron_command[i].command.est = atoi(estimateTime);
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
            printf("Error: Command \"%s\" cannot find right estimate time.\n", cron_command[i].command.cmd);
            exit(EXIT_FAILURE);
        }
    }
}

// Function: ckState(time_struct)
// Description: 
// 1.   Run over all the programs in the cron_command list not running and check if they should start running, 
//      if yes then run the program (change the state to Ture, reset the remaining_minutes, time + 1, proccess_count + 1) print the program name and time left to finish.
// 2.   Run over all the programs in the cron_command list running and check if they should stop running,
//      if yes then run the program (change the state to False) print the program name and says it is finish.
//      if no then remaining_minutes - 1 and print the program name and time left to finish.
// 3.   return and print the number of commands that is running. print the number of commands that starts running is the number of commands that is finish running.
int ckState(time_struct now)
{
    int running_commands = 0;
    for (int i = 0; i < total_cron_lines; i++)
    {
        if (cron_command[i].state == false &&
            isitTime(cron_command[i].command.sch_minute, now.minute) &&
            isitTime(cron_command[i].command.sch_hour, now.hour) &&
            isitTime(cron_command[i].command.sch_date, now.date) &&
            isitTime(cron_command[i].command.sch_month, now.month) &&
            isitTime(cron_command[i].command.sch_day_of_week, now.day_of_week))
        {
            cron_command[i].state = true;
            cron_command[i].remaining_minutes = cron_command[i].command.est - 1;
            cron_command[i].time++;
            proccess_count++;
            running_commands++;
        }
        else if (cron_command[i].state == true &&
                 cron_command[i].remaining_minutes == 0)
        {
            cron_command[i].state = false;
        }
        else if (cron_command[i].state == true &&
                 cron_command[i].remaining_minutes > 0)
        {
            cron_command[i].remaining_minutes--;
        }
    }
    return running_commands;
}

// Function: time_simulator(int)
// Description: This function simulates the siquation of every minute in the target month
// and record the data we interested in (we assume that the target month is in the current year),
// and return the array of the data we interested in.
int time_simulator(int month)
{
    time_struct tm;
    tm.month = month;
    int max_process_num = 0;
    for (tm.date = 1; tm.date <= getDaysInMonth(tm.month); tm.date++)
    {
        tm.day_of_week = getDayOfWeek(tm.month, tm.date);
        for (tm.hour = 0; tm.hour < VALID_HOURS; tm.hour++)
        {
            for (tm.minute = 0; tm.minute < VALID_MINUTES; tm.minute++)
            {
                int num_proccess = ckState(tm);
                if (num_proccess > max_process_num)
                {
                    max_process_num = num_proccess;
                }
            }
        }
    }
    return max_process_num;
}

int main(int argc, char *argv[])
{
    // check if the number of arguments is correct
    // read the arguments if correct, otherwise print error
    if (argc != 4)
    {
        printf("Error: Wrong number of arguments. take 3 but %d found.\n", argc - 1);
        exit(EXIT_FAILURE);
    }
    else
    {
        for (int i = 0; i < VALID_MONTHS_LIST_SIZE; i++)
        {
            if (strcmp(argv[1], "*") != 0 && strcmp(argv[1], valid_month[i]) == 0)
            {
                month = chgMonthFomat(argv[1]);
                break;
            } else if (i == VALID_MONTHS_LIST_SIZE - 1){
                printf("\"%s\" is not a valid argument for month. Take 0 to 11 or \"jan\" to \"dec\"\n", argv[1]);
                exit(EXIT_FAILURE);
            }
        }
        crontab_file = argv[2];
        estimates_file = argv[3];
    }
    
    precheck(crontab_file);                                                             // precheck the crontab-file and estimate-file
    precheck(estimates_file);
    
    cron_command = malloc(MAX_LIST_SIZE * sizeof(record_pad));                          // malloc the memory for the cron_command list at MAX_LIST_SIZE

    read_crontab_file();                                                                // read the crontab-file and estimates-file

    cron_command = realloc (cron_command, total_cron_lines * sizeof(record_pad));       //after read crontab-file, we can asure the mem cron_command need
    count_list = malloc(total_cron_lines * sizeof(int));                                // malloc the memory for the count_list according to the total_cron_lines

    read_estimates_file();                                                              // read the estimates-file
    check_cron_list();                                                                  // check if the estimates are valid

    // print the cron commands, just for debugging
    printf("----------------------------------------------------\n");
    printf("id\tminu\thour\tdate\tmonth\tday\test\tcommand\n");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < total_cron_lines; i++)
    {
        printf("| %i |\t%i\t%i\t%i\t%i\t%i\t%i\t%s\n", i,
               cron_command[i].command.sch_minute,
               cron_command[i].command.sch_hour,
               cron_command[i].command.sch_date,
               cron_command[i].command.sch_month,
               cron_command[i].command.sch_day_of_week,
               cron_command[i].command.est,
               cron_command[i].command.cmd);
        ;
    }
    printf("\n");

    int max_process_num = time_simulator(month);                                        // simulate the time in the target month
    printf("%s %d %d\n", findchamp().command.cmd, proccess_count, max_process_num);     // print out the required information

    free(cron_command);
    free(count_list);
    return 0;
}