#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

bool leapyear(int year) {
    return (year % 4 == 0 && year % 100 != 0 || year % 400 == 0);
}

int Monthday(int month, int year) {
    switch (month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        case 2:
            if (leapyear(year)) {
                return 29;
            } else {
                return 28;
            }
        default:
            return 0;
    }
}

// Calculate how many days before the first day of the month in the year.
int Daybefore(int month, int year) {
    int i, sum = 0;
    for (i = 1; i < month; i++) {
        sum += Monthday(i, year);
    }
    return sum;
}

void printCalendar(int month, int year) {
    int i, j, k, day, daysInMonth, firstDayOfMonth, lastDayOfMonth;
    char *week[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    daysInMonth = Monthday(month, year);
    firstDayOfMonth = ((year-2001)+(int)floor((year-2001)/4)-(int)floor((year-2001)/100)+(int)floor((year-2001)/400)+Daybefore(month, year))%7 + 1;
    lastDayOfMonth = (firstDayOfMonth + daysInMonth - 1) % 7;
    printf("\t\t%s %d\n", months[month - 1], year);
    printf("Sun\tMon\tTue\tWed\tThu\tFri\tSat\n");
    for (i = 0; i < firstDayOfMonth; i++) {
        printf("\t");
    }
    for (i = 1; i <= daysInMonth; i++) {
        printf("%d\t", i);
        if (((i + firstDayOfMonth) % 7) == 0) {
            printf("\n");
        }
    }
    for (i = 0; i < (7 - lastDayOfMonth); i++) {
        printf("\t");
    }
    printf("\n");
}

int main(){
    time_t realtime;
    time(&realtime);
    struct tm *timeinfo = localtime(&realtime);
    int year = timeinfo->tm_year + 1900;
    int month = timeinfo->tm_mon + 1;
    printCalendar(month, year);
    getchar();
    return 0;
}