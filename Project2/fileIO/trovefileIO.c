//  CITS2002 Project 2 2022
//  Student:   23006364   HU   ZHUO   100

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
        TROVE_FILE_P = popen(cmd, "r");
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

// LOAD THE WORDS FROM THE TROVE FILE INTO THE HASHTABLE
void load_from_troveFile(char *filename, char *wordslist, HASHTABLE_MLIST *hashtable)
{
    char *word = (char *)malloc(sizeof(char) * 1);
    memset(word, '\0', 1);
    int len = 0;
    char tmp[20000];
    tmp[0] = '\0';
    char c = *wordslist;

    while (c != '\0')
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
        c = *(++wordslist);
    }

    free(word);
}

HASHTABLE_MLIST *trovefile_load(void)
{
    HASHTABLE_MLIST *hashtable_mlist = hashtable_mlist_new();
    trovefile_open();

    while (!feof(TROVE_FILE_P))
    {
        char *filename = getLine(TROVE_FILE_P);
        char *wordslist = getLine(TROVE_FILE_P);
        load_from_troveFile(filename, wordslist, hashtable_mlist);
    }
    fclose(TROVE_FILE_P);
    return hashtable_mlist;
}

// THE FOLLOWING 4 FUNCTIONS ARE USED TO READ THE HASHTABLE
// THEY ARE JUST A DIFFERENT VERSION OF XXX_print FUNCTIONS IN DATASTRUCT

// READ THE LIST
char *list_read(LIST *list)
{
    char *str = strdup("");
    char *space = " ";

    if (list != NULL)
    {
        while (list->next != NULL)
        {
            if (list->word != NULL)
            {
                str = (char *)realloc(str, sizeof(char) * (strlen(str) + strlen(list->word) + 2));
                strcat(str, space);
                strcat(str, list->word);
            }
            list = list->next;
        }
        if (list->next == NULL)
        {
            if (list->word != NULL)
            {
                str = (char *)realloc(str, sizeof(char) * (strlen(str) + strlen(list->word) + 1));
                strcat(str, space);
                strcat(str, list->word);
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
                str_hashtable_list = hashtable_list_read(mlist->words);
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
            str_hashtable_list = hashtable_list_read(mlist->words);
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
    HASHTABLE_MLIST *old_hashtable = trovefile_load();
    hashtable_mlist_update(old_hashtable, hashtable);
    trovefile_write(old_hashtable);
}

// PRINT EVERYTHING IN THE TROVE FILE
void trovefile_print(void)
{
    HASHTABLE_MLIST *hashtable = trovefile_load();
    hashtable_mlist_print(hashtable);
    hashtable_mlist_free(hashtable);
    printf("\n");
}

// PRINT ALL THE FILENAME IN THE TROVE FILE
void trovefile_filename_print(void)
{
    HASHTABLE_MLIST *hashtable = trovefile_load();
    hashtable_mlist_filename_print(hashtable);
    hashtable_mlist_free(hashtable);
    printf("\n");
}