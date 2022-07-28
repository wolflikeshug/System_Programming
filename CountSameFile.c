#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define array_size 1024

// list all the filenames in the directory and store them in an array
void list_files(char *dirname, char *files[])
{
    char command[array_size];
    char filename[array_size];
    int i = 0;
    sprintf(command, "ls %s", dirname);
    FILE *fp = popen(command, "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    while (fgets(filename, array_size, fp) != NULL)
    {
        files[i] = strdup(filename);
        i++;
    }
    pclose(fp);
}

// print the sha256 hash of the file in the list one by one
void print_hash(char *filesname[])
{
    char command[array_size];
    strcpy(command, "sha256sum ");
    char result[array_size];
    char *token;
    int i = 0;
    while(filesname[i] != NULL) {
        strcat(command, filesname[i]);
        strcat(command, "");
        i++;
    }
    *result = system(command);
    token = strtok(result, " ");
    while(token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, " ");
    }
}


void main()
{
    char *filesname[array_size];
    list_files(".", filesname);
    // char *list[array_size] = {"testread.txt","CountSameFile.c"};
    print_hash(filesname);
}