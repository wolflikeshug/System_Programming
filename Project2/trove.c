#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE

#include "trove.h"

// fopen the target file and record all the words in the file
void update_process(char *filename, HASHTABLE_MLIST *hashtable)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    char *fileRealPath = (char *)malloc(PATH_MAX);
    realpath(filename, fileRealPath);
    recordWord(fp, filename, hashtable);
    fclose(fp);
}

int main(int argc, char *argv[])
{
    int optind;
    int result;
    int file_list_size = argc - 2;

    bool index_change = false;
    bool length_change = false;
    bool rebuild = false;
    bool update = false;
    bool remove = false;

    FILE *indexFile;

    while ((result = getopt(argc, argv, "f:brul:")) != -1)
    {
        switch (result)
        {
        case 'f':
            if (optarg != NULL)
            {
                index_change = true;
            }
            else
            {
                perror("No index file name");
                exit(EXIT_FAILURE);
            }
        case 'l':
            if (optarg != NULL)
            {
                for (int i = 0; i < strlen(optarg); i++)
                {
                    if (isdigit(optarg[i]) == 0)
                    {
                        perror("Invalid length number");
                        exit(EXIT_FAILURE);
                    }
                }
                length_change = true;
            }
            else
            {
                perror("No length number");
                exit(EXIT_FAILURE);
            }
        case 'b':
            rebuild = true;
            break;
        case 'r':
            remove = true;
            break;
        case 'u':
            update = true;
            break;
        case '?':
            break;
        }
    }

    if (index_change)
    {
        change_index_file(optarg);
        file_list_size -= 2;
    }

    if (length_change)
    {
        change_keylen(atoi(optarg));
        file_list_size -= 2;
    }

    char *filelist[file_list_size];
    int i = 0;

    for (; optind < argc; optind++)
    {
        filelist[i] = argv[optind];
        i++;
    }

    if (rebuild)
    {
        indexFile = fopen(INDEX_FILE, "w");
        HASHTABLE_MLIST *hashtable = hashtable_mlist_new();
        for (int i = 0; i < file_list_size; i++)
        {
            update_process(filelist[i], hashtable);
        }
        indexfile_replace(indexFile, hashtable);
    }

    if (update)
    {
        indexFile = fopen(INDEX_FILE, "r");
        if (indexFile == NULL)
        {
            perror("No index file");
            exit(EXIT_FAILURE);
        }
        indexFile = fopen(INDEX_FILE, "w");
        HASHTABLE_MLIST *hashtable = hashtable_mlist_new();
        indexfile_load(indexFile, hashtable);
        for (int i = 0; i < file_list_size; i++)
        {
            update_process(filelist[i], hashtable);
        }
        indexfile_replace(indexFile, hashtable);
    }

    if (remove)
    {
        indexFile = fopen(INDEX_FILE, "r");
        if (indexFile == NULL)
        {
            perror("No index file");
            exit(EXIT_FAILURE);
        }
        indexFile = fopen(INDEX_FILE, "w");
        HASHTABLE_MLIST *hashtable = hashtable_mlist_new();
        indexfile_load(indexFile, hashtable);
        for (int i = 0; i < file_list_size; i++)
        {
            hashtable_mlist_remove(hashtable, filelist[i]);
        }
        indexfile_replace(indexFile, hashtable);
    }

    if (!rebuild && !update && !remove && !length_change)
    {
        indexFile = fopen(INDEX_FILE, "r");
        if (indexFile == NULL)
        {
            perror("No index file");
            exit(EXIT_FAILURE);
        }
        HASHTABLE_MLIST *hashtable = hashtable_mlist_new();
        indexfile_load(indexFile, hashtable);
        for (int i = 0; i < file_list_size; i++)
        {
            if (hashtable_mlist_find(hashtable, filelist[i]))
            {
                printf("%s\n", filelist[i]);
            }
        }
    }

    fclose(indexFile);
    return 0;
}