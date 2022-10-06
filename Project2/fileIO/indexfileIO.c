#define _POSIX_C_SOURCE 200809L

#include "indexfileIO.h"

char *INDEX_FILE = "/tmp/trove";

// CHANGE THE INDEX FILE NAME
void change_index_file(char *filename)
{
    INDEX_FILE = strdup(filename);
}

// CREATE A NEW INDEX FILE IF THERE ISN'T ONE ALREADY, OTHERWISE OPEN IT
FILE *indexfile_init(void)
{
    FILE *fp = fopen(INDEX_FILE, "r");
    if (fp == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    return fp;
}

// READ THE INDEX FILE AND LOAD THE HASHTABLE FROM IT
// THIS IS NOT A EASY TASK, BECAUSE THE INDEX FILE IS A BINARY FILE STORING A COMPLEX STRUCTURE
// 1. READ THE HASHTABLE_MLIST OUT (WHICH IS AN ARRAY)
// 2. READ THE MLIST OUT (WHICH IS A MLIST *， SO ALLOCATE SPACE FOR IT)
// 3.THEN READ THE "filename" OUT (WHICH IS A CHAR * SO NEED A DYNAMIC ALLOCATION)
// 4.THEN READ THE "keys" OUT (WHICH IS A HASHTABLE_LIST * SO NEED A DYNAMIC ALLOCATION)
//      4.1 READ THE LIST OUT (WHICH IS A LIST * SO NEED A DYNAMIC ALLOCATION)
//      4.2 READ THE "string" OUT (WHICH IS A CHAR * SO NEED A DYNAMIC ALLOCATION)
//      4.3 READ THE "next" OUT (REPETITION OF 4.1-4.3 UNLESS THE NEXT IS NULL)) 
// 5.THEN READ THE "next" OUT ONE BY ONE (REPEAT STEP 2-5 UNTIL THE "next" IS NULL)
void indexfile_load(FILE *fp, HASHTABLE_MLIST *hashtable)
{
    // TODO: implement this function

}

// REMOVE THE OLD DATA AND REPLACE IT WITH THE NEW ONE
void indexfile_replace(FILE *indexFile, HASHTABLE_MLIST *hashtable)
{
    fseek(indexFile, 0, SEEK_SET);
    fwrite(hashtable, sizeof(HASHTABLE_MLIST), 1, indexFile);
    free(hashtable);
}

// UPDATE THE OLD HASHTABLE WHICH HAVING THE SAME FILE NAME AS IN NEW WHILE KEEPING THE OTHER DATA
void indexfile_update(FILE *indexFile, HASHTABLE_MLIST *hashtable)
{
    HASHTABLE_MLIST *old_hashtable = hashtable_mlist_new();
    char* p = realloc(old_hashtable, file_getsize(indexFile));
    indexfile_load(indexFile, old_hashtable);
    hashtable_mlist_update(old_hashtable, hashtable);
    indexfile_replace(indexFile, old_hashtable);
    free(hashtable);
    free(p);
}

// CLOSE THE INDEX FILE
void indexfile_close(FILE *indexFile)
{
    fclose(indexFile);
}
