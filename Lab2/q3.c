//
// Created by HuggingWolf on 2022/8/17.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char* argv[]){
// print out the biggest num in argv
    int i, max = 0;
    for (i = 1; i < argc; i++){
        if (atoi(argv[i]) > max){
            max = atoi(argv[i]);
        }
    }
    printf("%d\n", max);
    return 0;
}