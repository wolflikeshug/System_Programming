/*
 *   CITS2002  Project 2  2022-sem2
 *   Student:  23006364   HU ZHUO   100
 */

#include "wordFileIO.h"

HASHTABLE_MLIST *hashtable_global;

// RECORD ALL THE WORDS FROM FILE INTO THE HASHTABLE
void recordWord_file(char *filename, HASHTABLE_MLIST *hashtable)
{
    filename = getRealPath(filename);
    printf("\t%s\n", filename);
    FILE *fp = openfile(filename);

    char *word = (char *)malloc(sizeof(char) * 1);
    CHECK_MEM(word);
    memset(word, '\0', 1);

    char *tmp = (char *)malloc(sizeof(char) * 1);
    CHECK_MEM(tmp);
    memset(tmp, '\0', 1);

    uint32_t len = 0;

    char c = fgetc(fp);
    while (!feof(fp))
    {
        if (isalnum(c))
        {
            tmp = realloc(tmp, sizeof(char) * (len + 2));
            tmp[len] = c;
            len++;
        }
        else
        {
            tmp[len] = '\0';
            word = strdup(tmp);
            len = 0;

            free(tmp);

            tmp = (char *)malloc(sizeof(char) * 1);
            CHECK_MEM(tmp);
            memset(tmp, '\0', 1);

            if (wordlen_check(word))
            {
                hashtable_mlist_add(hashtable, filename, word);
            }
        }
        c = fgetc(fp);
    }

    fclose(fp);
    free(word);
    free(tmp);
}

// RECORD ALL THE WORDS FROM FILE INTO THE HASHTABLE
void *recordWord_file_thread(void *thread_data)
{
    char *filename = (char *)thread_data;
    recordWord(filename, hashtable_global);
    pthread_exit(NULL);
}

// IF THE NAME INPUTED IS A DIRECTORY, TRAVESE THE DIRECTORY AND RECORD ALL THE FILES AND DO recordWord_dir() TO THE SUB DIRECTORIES
void recordWord_dir(char *filename, HASHTABLE_MLIST *hashtable)
{
    DIR *dir;
    struct dirent *ptr;
    char path[PATH_MAX];
    uint32_t NUM_THREADS = SHRT_MAX;
    pthread_t threads[NUM_THREADS];
    uint32_t tid = 0;

    printf("\tOpening Directory:\t%s\n", filename);
    dir = opendir(filename);

    if (dir == NULL)
    {
        perror("OPEN DIR ERROR");
        exit(EXIT_FAILURE);
    }

    while ((ptr = readdir(dir)) != NULL)
    {
        if (!strcmp(ptr->d_name, ".") || !strcmp(ptr->d_name, ".."))
        {
            continue;
        }
        else if (ptr->d_type == 8)
        {
            strcpy(path, filename);
            strcat(path, "/");
            strcat(path, ptr->d_name);
            char * thread_data = strdup(path);
            struct stat statbuf;
            int ret = stat (filename, &statbuf);
            if (ret)
            {
                perror("stat");
                exit(EXIT_FAILURE);
            }

            int32_t rc = pthread_create(&threads[tid], NULL, recordWord_file_thread, (void *)thread_data);

            if (rc != 0)
            {
                printf("ERROR; return code from pthread_create() is %d\n", rc);
                exit(EXIT_FAILURE);
            }
            usleep(statbuf.st_size%10);
            tid ++;
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
    hashtable_global = hashtable;

    struct stat statbuf;
    if (stat(filename, &statbuf))
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    else if (S_ISDIR(statbuf.st_mode))
    {
        recordWord_dir(filename, hashtable);
    }
    else if (S_ISREG(statbuf.st_mode))
    {
        recordWord_file(filename, hashtable);
    }
}

