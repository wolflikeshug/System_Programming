#include <stdio.h>

//read text from a file
void readfile(char *filename)
{
    FILE *fp;
    char ch;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    while ((ch = fgetc(fp)) != EOF)
    {
        printf("%c", ch);
    }
    fclose(fp);
}