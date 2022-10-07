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
    char *cmd = (char *)malloc(sizeof(char) * ARG_MAX);
    strcpy(cmd, "zcat '");
    strcat(cmd, TROVE_FILE);
    strcat(cmd, "'");
    if (file_exist(TROVE_FILE))
    {
        TROVE_FILE_P = popen(cmd, "r+");
    }
}

// CLOSE THE TROVE FILE AND GZIP IT
void trovefile_gz_close(void)
{
    fclose(TROVE_FILE_P);
    
    char *cmd = (char *)malloc(sizeof(char) * ARG_MAX);
    strcpy(cmd, "gzip -9 '");
    strcat(cmd, TROVE_FILE);
    strcat(cmd, "'");
    system(cmd);
    strcpy(cmd, "mv '");
    strcat(cmd, TROVE_FILE);
    strcat(cmd, ".gz' '");
    strcat(cmd, TROVE_FILE);
    strcat(cmd, "'");
    system(cmd);
}


HASHTABLE_MLIST *trovefile_load(void)
{
    // TODO: implement this function
    HASHTABLE_MLIST *hashtable_mlist = hashtable_mlist_new();
    TROVE_FILE_P = openfile(TROVE_FILE);



    fclose(TROVE_FILE_P);
    return hashtable_mlist;
}

// THE FOLLOWING FOUR FUNCTIONS ARE USED TO WRITE THE HASHTABLE TO THE TROVE FILE
// THEY ARE JUST A DIFFERENT VERSION OF _print FUNCTIONS IN DATASTRUCT

// READ THE LIST
char *list_read(LIST *list)
{
    char *str = strdup("");
    char *space = " ";

    if (list != NULL)
    {
        while (list->next != NULL)
        {
            if(list->keyword != NULL)
            {
                str = (char *)realloc(str, sizeof(char) * (strlen(str) + strlen(list->keyword) + 2));
                strcat(str, space);
                strcat(str, list->keyword);
            }
            list = list->next;
        }
        if (list->next == NULL)
        {
            if(list->keyword != NULL)
            {
                str = (char *)realloc(str, sizeof(char) * (strlen(str) + strlen(list->keyword) + 1));
                strcat(str, space);
                strcat(str, list->keyword);
            }
        }
    }
    return str;
}

// READ THE HASHTABLE
char *hashtable_list_read(HASHTABLE_LIST *hashtable)
{
    char *str = strdup("");
    char *str_list;


    for (int i = 0; i < HASHTABLE_LIST_SIZE; i++)
    {
        LIST *list = hashtable[i];
        if (list != NULL)
        {
            str_list = list_read(list);
        }
        str = (char *)realloc(str, sizeof(char) * (strlen(str) + strlen(str_list) + 1));
        strcat(str, str_list);
    }
    return str;
}

// READ the MLIST
char *mlist_read(MLIST *mlist)
{
    char *str = strdup("");
    char *str_hashtable_list;
    char *linespace = "\n";

    if (mlist != NULL)
    {
        while (mlist->next != NULL)
        {
            if (mlist->filename != NULL)
            {
                char *str_filename = strdup(mlist->filename);
                str = (char *)realloc(str, sizeof(char) * (strlen(str) + strlen(str_filename) + 2));
                strcat(str, str_filename);
                strcat(str, linespace);
                str_hashtable_list = hashtable_list_read(mlist->keys);
                str = (char *)realloc(str, sizeof(char) * (strlen(str) + strlen(str_hashtable_list) + 2));
                strcat(str, str_hashtable_list);
                strcat(str, linespace);
            }
            mlist = mlist->next;
        }
        if (mlist->next == NULL && mlist->filename != NULL)
        {
            char *str_filename = strdup(mlist->filename);
            str_filename = realloc(str_filename, sizeof(char) * (strlen(str_filename) + strlen(mlist->filename) + 2));
            strcat(str, str_filename);
            strcat(str, linespace);
            str_hashtable_list = hashtable_list_read(mlist->keys);
            str = (char *)realloc(str, sizeof(char) * (strlen(str) + strlen(str_hashtable_list) + 2));
            strcat(str, str_hashtable_list);
            strcat(str, linespace);
        }
    }
    return str;
}

//  READ the hashtable
char *hashtable_mlist_read(HASHTABLE_MLIST *hashtable)
{
    char *str = strdup("");
    char *str_mlist;

    for (int i = 0; i < HASHTABLE_MLIST_SIZE; i++)
    {
        if (hashtable[i] != NULL)
        {
            str_mlist = mlist_read(hashtable[i]);
            str = (char *)realloc(str, sizeof(char) * (strlen(str) + strlen(str_mlist) + 1));
            strcat(str, str_mlist);
        }
    }
    return str;
}


// REMOVE THE OLD DATA AND REPLACE IT WITH THE NEW ONE
void trovefile_write(HASHTABLE_MLIST *hashtable)
{
    TROVE_FILE_P = fopen(TROVE_FILE, "w+");
    fseek(TROVE_FILE_P, 0, SEEK_SET);

    char *str = hashtable_mlist_read(hashtable);
    fprintf(TROVE_FILE_P, "%s", str);

    hashtable_mlist_free(hashtable);
    trovefile_gz_close();
}

// UPDATE THE OLD HASHTABLE WHICH HAVING THE SAME FILE NAME AS IN NEW WHILE KEEPING THE OTHER DATA
void trovefile_update(HASHTABLE_MLIST *hashtable)
{
    HASHTABLE_MLIST *old_hashtable = hashtable_mlist_new();
    char* p = realloc(old_hashtable, file_getsize(TROVE_FILE_P));
    old_hashtable = trovefile_load();
    hashtable_mlist_update(old_hashtable, hashtable);
    trovefile_write(old_hashtable);
    hashtable_mlist_free(hashtable);
    free(p);
}

