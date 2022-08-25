#include <stdlib.h>

int q1(char *string){
    int size = sizeof(string);
    return size/sizeof(char);
}