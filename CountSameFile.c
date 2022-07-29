#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define array_size 1024
#define sha256_size 128

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

// store the sha256 hash of the file in the list one by one
void print_hash(char *filesname[], char *output[])
{
    char command[array_size];
    char *token;
    int i = 0;
    while(filesname[i] != NULL) {
        strcat(command, "sha256sum ");
        strcat(command, filesname[i]);
        i++;
    }
    printf(command);
    printf("%i\n",system(command));
    *command = system(command);
    printf(command);
    // split the string into two parts: the filename and the hash
    token = strtok(command, " ");
    i = 0;
    while (token != NULL)
    {
        strcpy(output[i], token);
        i++;
        token = strtok(NULL, " ");
    }
}

// check the chars in the array if they are the same
// if they are the same, print the value
void check_same(char *hash[])
{
    int i = 0;
    int j = 1;
    while(hash[i] != NULL) {
        while(hash[j] != NULL) {
            if(strcmp(hash[i], hash[j]) == 0) {
                printf("%s\n", hash[i]);
            }
            j++;
        }
        i++;
        j = i+1;
    }
}

void main()
{
    char *files[array_size];
    char *output[array_size];
    list_files(".", files);
    print_hash(files,output);
    printf("============================\n");
    check_same(output);
    printf(*output);
    exit(0);
}