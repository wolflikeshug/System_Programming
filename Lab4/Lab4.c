#include "Lab4.h"

void main(int argc, char* argv[]){
    char *str1 = "Hello";
    char *str2 = "Hello";
    bool str3 = strcmp_pointer(str1, str2);
    if (str3 == true){
        printf("The strings are the same");
    }
    else{
        printf("The strings are not the same");
    }
}
