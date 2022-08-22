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
