//
// Created by HuggingWolf on 2022/8/17.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main (int argc, char* argv[]){
    //add up odd digits of argv[1] as sum1
    //add up even digits of argv[1] as sum2
    int i = 0;
    int sum1 = 0;
    int sum2 = 0;
    int num = atoi(argv[1]);
    while(num > 0){
        if(i % 2 == 0){
            sum1 += num % 10;
        }
        else{
            sum2 += num % 10;
        }
        num /= 10;
        i++;
    }
    if ((sum1 +sum2 *2) %10 == 0){
        printf("The card num is valid\n");
    }
    else{
        printf("Error\n");
    }
}