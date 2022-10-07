#define _POSIX_C_SOURCE 20089L
#define _GNU_SOURCE


#include "trovefileIO.h"

char *TROVE_FILE = "/tmp/trove";
FILE *TROVE_FILE_P = NULL;

// CHANGE THE TROVE FILE NAME
void change_trove_file(char *filename)
{
    TROVE_FILE = strdup(filename);
}

// OPEN THE TROVE FILE
void trovefile_open(void)
{
    TROVE_FILE_P = fopen(TROVE_FILE, "r+");
    if (TROVE_FILE_P == NULL)
    {
        TROVE_FILE_P = fopen(TROVE_FILE, "w+");
    }
}

// CLEAR THE TROVE FILE FOR REWRITING
void trovefile_open_rewrite(void)
{
    TROVE_FILE_P = fopen(TROVE_FILE, "w+");
}

// CLOSE THE TROVE FILE
void trovefile_close(void)
{
    fclose(TROVE_FILE_P);
}






HASHTABLE_MLIST *trovefile_load(void)
{
    // TODO: implement this function
    HASHTABLE_MLIST *hashtable_mlist = hashtable_mlist_new();
    TROVE_FILE_P = openfile(TROVE_FILE);



    trovefile_close();
    return hashtable_mlist;
}

// REMOVE THE OLD DATA AND REPLACE IT WITH THE NEW ONE
void trovefile_replace(HASHTABLE_MLIST *hashtable)
{
    trovefile_open_rewrite();
    fseek(TROVE_FILE_P, 0, SEEK_SET);

    hashtable_mlist_free(hashtable);
    trovefile_close();
}

// UPDATE THE OLD HASHTABLE WHICH HAVING THE SAME FILE NAME AS IN NEW WHILE KEEPING THE OTHER DATA
void trovefile_update(HASHTABLE_MLIST *hashtable)
{
    HASHTABLE_MLIST *old_hashtable = hashtable_mlist_new();
    char* p = realloc(old_hashtable, file_getsize(TROVE_FILE_P));
    old_hashtable = trovefile_load();
    hashtable_mlist_update(old_hashtable, hashtable);
    trovefile_replace(old_hashtable);
    hashtable_mlist_free(hashtable);
    free(p);
}

