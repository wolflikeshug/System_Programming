//
// Created by HuggingWolf on 2022/8/17.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// take one argument in, if the number can be divided by 400 or can be divided by 4 and not be divided by 100, print "leap year", otherwise return print "not leap year"
void main(int argc, char* argv[]){
    if(argc != 2){
        printf("Usage: ./q1 <year>\n");
        exit(1);
    }
    int year = atoi(argv[1]);
    if(year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)){
        printf("leap year\n");
    }else{
        printf("not leap year\n");
    }
}