#define _POSIX_C_SOURCE 20089L
#define _GNU_SOURCE

#include "trove.h"

// fopen the target file and record all the words in the file
void update_process(char *filename, HASHTABLE_MLIST *hashtable)
{
    FILE *fp = fopen(filename);
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

    bool trove_change = false;
    bool length_change = false;
    bool rebuild = false;
    bool update = false;
    bool remove = false;

    FILE *troveFile;

    while ((result = getopt(argc, argv, "f:brul:")) != -1)
    {
        switch (result)
        {
        case 'f':
            if (optarg != NULL)
            {
                trove_change = true;
            }
            else
            {
                perror("No trove file name");
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

    if (trove_change)
    {
        change_trove_file(optarg);
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
        troveFile = fopen(TROVE_FILE, "w");
        HASHTABLE_MLIST *hashtable = hashtable_mlist_new();
        for (int i = 0; i < file_list_size; i++)
        {
            update_process(filelist[i], hashtable);
        }
        trovefile_replace(troveFile, hashtable);
    }

    if (update)
    {
        troveFile = fopen(TROVE_FILE, "r");
        if (troveFile == NULL)
        {
            perror("No trove file");
            exit(EXIT_FAILURE);
        }
        troveFile = fopen(TROVE_FILE, "w");
        HASHTABLE_MLIST *hashtable = hashtable_mlist_new();
        trovefile_load(troveFile, hashtable);
        for (int i = 0; i < file_list_size; i++)
        {
            update_process(filelist[i], hashtable);
        }
        trovefile_replace(troveFile, hashtable);
    }

    if (remove)
    {
        troveFile = fopen(TROVE_FILE, "r");
        if (troveFile == NULL)
        {
            perror("No trove file");
            exit(EXIT_FAILURE);
        }
        troveFile = fopen(TROVE_FILE, "w");
        HASHTABLE_MLIST *hashtable = hashtable_mlist_new();
        trovefile_load(troveFile, hashtable);
        for (int i = 0; i < file_list_size; i++)
        {
            hashtable_mlist_remove(hashtable, filelist[i]);
        }
        trovefile_replace(troveFile, hashtable);
    }

    if (!rebuild && !update && !remove && !length_change)
    {
        troveFile = fopen(TROVE_FILE, "r");
        if (troveFile == NULL)
        {
            perror("No trove file");
            exit(EXIT_FAILURE);
        }
        HASHTABLE_MLIST *hashtable = hashtable_mlist_new();
        trovefile_load(troveFile, hashtable);
        for (int i = 0; i < file_list_size; i++)
        {
            if (hashtable_mlist_find(hashtable, filelist[i]))
            {
                printf("%s\n", filelist[i]);
            }
        }
    }

    fclose(troveFile);
    return 0;
}