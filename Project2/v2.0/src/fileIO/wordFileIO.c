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

    printf("\t%s\n", filename); // Print the name of the file
    FILE *fp = openfile(filename);

    char *word = (char *)calloc(2, sizeof(char));
    CHECK_MEM(word);

    char *tmp = (char *)calloc(1, sizeof(char));
    CHECK_MEM(tmp);

    uint32_t len = 0;

    char c = fgetc(fp);
    while (!feof(fp))
    {
        if (isalnum(c))
        {
            if (len >= 20)
            {
                tmp = realloc(tmp, sizeof(char) * (len + 2));
            }
            tmp[len] = c;
            len++;
        }
        else
        {
            tmp[len] = '\0';
            word = strdup(tmp);
            len = 0;

            free(tmp);

            tmp = (char *)calloc(2, sizeof(char));
            CHECK_MEM(tmp);

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

// THREADED recordWord_file FUNCTION
void *recordWord_file_thread(void *thread_data)
{
    char *filename = (char *)thread_data;
    recordWord(filename, hashtable_global);
    pthread_exit(NULL);
}

// TRAVESE THE DIRECTORY AND RECORD ALL THE FILES USE recordWord_file_thread
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
            char *thread_data = strdup(path);
            int32_t rc = pthread_create(&threads[tid], NULL, recordWord_file_thread, (void *)thread_data);

            if (rc != 0)
            {
                printf("ERROR; return code from pthread_create() is %d\n", rc);
                exit(EXIT_FAILURE);
            }
            usleep(1000);
            tid++;
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
