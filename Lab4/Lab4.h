#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

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

int strlen_pointer( char *strp )    
{
    char   *s = strp;

    while( *s != '\0' ) {
        ++s;
    }
    return (s - strp);
}

char *strcat_pointer(char *str1, char *str2){
    char *str3 = (char *)malloc(strlen(str1) + strlen(str2) + 1);
    char *strsav = str3;
    while(*str1 != '\0'){
        *str3 = *str1;
        str1++;
        str3++;
    }
    str1 -= strlen(strsav);
    while (*str2 != '\0'){
        *str3 = *str2;
        str2++;
        str3++;
    }
    *str3 = '\0';
    return strsav;
}

bool strcmp_pointer( char *str1, char *str2){
    while (*str1 != '\0' && *str2 != '\0'){
        if (*str1 != *str2){
            return false;
        }
        str1++;
        str2++;
    }
    if (*str1 == '\0' && *str2 == '\0'){
        return true;
    }
    else{
        return false;
    }
}

char *strchr_pointer(char *str, char ch){
    while (*str != '\0'){
        if (*str == ch){
            return str;
        }
        str++;
    }
    return NULL;
}

char *strrchr_pointer(char *str, char ch){
    char *pointer = NULL;
    while (*str != '\0'){
        if (*str == ch){
            pointer = str;
        }
        str++;
    }
    return pointer;
}

char *strpbrk_pointer(char *str1, char *str2){
    while (*str1 != '\0'){
        char *str2p = str2;
        while (*str2p != '\0'){
            if (*str1 == *str2p){
                return str2p;
            }
            str2p++;
        }
        str1++;
    }
    return NULL;
}

char *strstr_pointer(char *str1, char *str2){
    char *str1sav = str1;
    char *str2sav = str2;
    while (*str1 != '\0'){
        if (*str1 == *str2){
            while (*str2 != '\0'){
                if (*str1 != *str2){
                    str2 = str2sav;
                    break;
                }
                str1++;
                str2++;
            }
            if (*str2 == '\0'){
                return str1sav;
            }
        }
        str1++;
        str1sav++;
    }
    return NULL;
}

