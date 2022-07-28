#include <stdio.h>

#define BUFFER_SIZE 1024
#define FILE_NAME "testread.txt"
// define a array named message to store the buffer
char message[BUFFER_SIZE];

// read text from a file and store the message in one array
void readfile(char *filename)
{
    FILE *fp;
    char ch;
    int i = 0;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    while ((ch = fgetc(fp)) != EOF)
    {
        message[i] = ch;
        i++;
    }
    fclose(fp);
}

// print the message
void printmessage()
{
    int i;
    for (i = 0; i < BUFFER_SIZE; i++)
    {
        if (message[i] == '\0')
        {
            break;
        }
        printf("%c", message[i]);
    }
}

void main()
{
    readfile(FILE_NAME);
    printmessage();
}
