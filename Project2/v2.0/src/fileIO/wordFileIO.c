/*
 *   CITS2002  Project 2  2022-sem2
 *   Student:  23006364   HU ZHUO   100
 */

#include "wordFileIO.h"

HASHTABLE_MLIST *hashtable;

// RECORD ALL THE WORDS FROM FILE INTO THE HASHTABLE
void recordWord_file(char *filename)
{
    filename = getRealPath(filename);
    printf("\t%s\n", filename);

    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        fclose(fp);
    }
    else
    {
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
}

// RECORD ALL THE WORDS FROM FILE INTO THE HASHTABLE MULTI-THREAD
void *recordWord_file_thread(void *thread_data)
{
    WORDIO_THREAD_DATA *data = (WORDIO_THREAD_DATA *)thread_data;
    char *filename = data->filename;

    filename = getRealPath(filename);
    printf("\t%s\n", filename);

    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        fclose(fp);
        pthread_exit(NULL);
    }
    else
    {
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
    pthread_exit(NULL);
    }
}

// IF THE NAME INPUTED IS A DIRECTORY, TRAVESE THE DIRECTORY AND RECORD ALL THE FILES AND DO recordWord_dir() TO THE SUB DIRECTORIES
void recordWord_dir(char *filename)
{
    DIR *dir;
    struct dirent *ptr;
    char path[PATH_MAX];

    uint32_t NUM_THREADS = 0;
    LIST *fileList = list_new();

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
            fileList = list_add(fileList, strdup(path));
            NUM_THREADS++;
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
            recordWord_dir(path);
        }
    }

    WORDIO_THREAD_DATA thread_data_array[NUM_THREADS];
    pthread_t threads[NUM_THREADS];

    for (uint32_t tid = 0; tid < NUM_THREADS; tid++)
    {
        if (fileList != NULL && fileList->word != NULL)
        {
            thread_data_array[tid].filename = strdup(fileList->word);
            fileList = fileList->next;
        }
    }

    uint32_t end = NUM_THREADS - 1;
    uint32_t tid = 0;
    while (tid < end)
    {
        int rc0 = pthread_create(&threads[tid], NULL, recordWord_file_thread, (void *)&thread_data_array[tid]);

        if (rc0 != 0)
        {
            printf("Error: return code from pthread_create() is %d", rc0);
            exit(EXIT_FAILURE);
        }

        int rc1 = pthread_create(&threads[end], NULL, recordWord_file_thread, (void *)&thread_data_array[end]);

        if (rc1 != 0)
        {
            printf("Error: return code from pthread_create() is %d", rc1);
            exit(EXIT_FAILURE);
        }

        tid++;
        end--;
    }

    closedir(dir);
}

// THE OVERALL FUNTION FOR RECORDING
void *recordWord(void *thread_data)
{
    struct wordIO_thread_data *data;
    data = (struct wordIO_thread_data *)thread_data;
    hashtable = data->hashtable;

    // printf(" %s:\n", data->filename);

    struct stat statbuf;
    if (stat(data->filename, &statbuf))
    {
        perror("stat");
        exit(EXIT_FAILURE);
    }
    else if (S_ISDIR(statbuf.st_mode))
    {
        recordWord_dir(data->filename);
    }
    else if (S_ISREG(statbuf.st_mode))
    {
        recordWord_file(data->filename);
    }
    pthread_exit(NULL);
}