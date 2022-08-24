#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIST_SIZE 21
#define MAX_LINE_SIZE 101

int main()
{
    char hello[MAX_LINE_SIZE] = "1 2 3 4 5";
    char *hello2;
    hello2 = strtok(hello, " ");
    int i = 0;
    while (i < 8)
    {
        hello2 = strtok(NULL, " ");
        if(hello2 == NULL)
        {
            printf("Error: Wrong format.\n");
            //exit(EXIT_FAILURE);
        }
        i++;
    }
    printf("%s\n", hello);
    printf("%d\n", i);
    return 0;
}