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
    return fopen(INDEX_FILE, "w+");
}

// READ THE INDEX FILE AND LOAD THE HASHTABLE FROM IT
void indexfile_load(FILE *indexfile, HASHTABLE_MLIST *hashtable)
{
    fseek(indexfile, 0, SEEK_SET);
    fread(hashtable, file_getsize(indexfile), 1, indexfile);
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
