//
// Created by huggingwolf on 8/08/22.
//

//check the input year is leap year or not
#include <stdio.h>

void main() {
    int year;
    printf("Enter the year: ");
    scanf("%d", &year);
    if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) {
        printf("%d is a leap year.\n", year);
    } else {
        printf("%d is not a leap year.\n", year);
    }
}