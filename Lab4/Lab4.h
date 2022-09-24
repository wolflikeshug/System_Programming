#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void money(int total, int *dollar, int *cents){
    *dollar = total / 100;
    *cents = total % 100;
}

int *maximum_a(int values[], int n){
    int max = values[0];
    int *pointer = &values[0];
    for (int i = 1; i < n; i++){
        if (values[i] > max){
            max = values[i];
            pointer = &values[i];
        }
    }
    return pointer;
}

int *maximum_p(int *values, int n){
    int max = values[0];
    int *pointer = &values[0];
    for (int i = 1; i < n; i++){
        if (values[i] > max){
            max = values[i];
            pointer = &values[i];
        }
    }
    return pointer;
}
