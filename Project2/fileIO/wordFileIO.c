//  CITS2002 Project 2 2022
//  Student:   23006364   HU   ZHUO   100

#include "wordFileIO.h"

// RECORD ALL THE WORDS FROM FILE INTO THE HASHTABLE
void recordWord_file(char *filename, HASHTABLE_MLIST *hashtable)
{
    filename = getRealPath(filename);
    printf("%s\n", filename);
    FILE *fp = openfile(filename);
    char *word = (char *)malloc(sizeof(char) * 1);
    memset(word, '\0', 1);
    int len = 0;
    char tmp[2000];
    tmp[0] = '\0';
    char c = fgetc(fp);
    while (!feof(fp))
    {
        if (isWord(c))
        {
            tmp[len] = c;
            len++;
        }
        else
        {
            tmp[len] = '\0';
            word = strdup(tmp);
            len = 0;
            tmp[len] = '\0';
            if (wordlen_check(word))
            {
                hashtable_mlist_add(hashtable, filename, word);
            }
        }
        c = fgetc(fp);
    }

    fclose(fp);
    free(word);
}

// IF THE NAME INPUTED IS A DIRECTORY, TRAVESE THE DIRECTORY AND RECORD ALL THE FILES AND DO recordWord_dir() TO THE SUB DIRECTORIES
void recordWord_dir(char *filename, HASHTABLE_MLIST *hashtable)
{
    DIR *dir;
    struct dirent *ptr;
    char path[PATH_MAX];

    printf("Opening Directory:\t%s\n", filename);
    dir = opendir(filename);

    if (dir == NULL)
    {
        perror("OPEN DIR ERROR");
        exit(EXIT_FAILURE);
    }

    while ((ptr = readdir(dir)) != NULL)
    {
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
        {
            continue;
        }
        else if (ptr->d_type == 8)
        {
            strcpy(path, filename);
            strcat(path, "/");
            strcat(path, ptr->d_name);
            recordWord_file(path, hashtable);
        }
        else if (ptr->d_type == 10)
        {
            continue;
        }
        else if (ptr->d_type == 4)
        {
            strcpy(path, filename);
            strcat(path, "/");
            strcat(path, ptr->d_name);
            printf("\n");
            recordWord_dir(path, hashtable);
        }
    }
    closedir(dir);
}

// THE OVERALL FUNTION FOR RECORDING
void recordWord(char *filename, HASHTABLE_MLIST *hashtable)
{
    if (isDirectory(filename))
    {
        recordWord_dir(filename, hashtable);
    }
    else if (isFile(filename))
    {
        recordWord_file(filename, hashtable);
    }
    else
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
}