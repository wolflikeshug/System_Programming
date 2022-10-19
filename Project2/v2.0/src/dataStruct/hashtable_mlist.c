/*
 *   CITS2002  Project 2  2022-sem2
 *   Student:  23006364   HU ZHUO   100
 */

#include "hashtable_mlist.h"

// ALLOCATE SPACE AND INITIALISE A NEW HASHTABLE_MLIST
HASHTABLE_MLIST *hashtable_mlist_new(void)
{
    HASHTABLE_MLIST *new = (HASHTABLE_MLIST *)calloc(HASHTABLE_MLIST_SIZE, sizeof(MLIST *));
    CHECK_MEM(new);

    for (uint16_t i = 0; i < HASHTABLE_MLIST_SIZE; i++)
    {
        new[i] = mlist_new();
    }
    return new;
}

// ADD NEW FILENAME TO THE HASHTABLE_MLISTT
void hashtable_mlist_add(HASHTABLE_MLIST *hashtable, char *filename, char *word)
{
    uint16_t hash = DJBHash(filename) % HASHTABLE_MLIST_SIZE;

    hashtable[hash] = mlist_add(hashtable[hash], filename);
    if (hashtable[hash]->words == NULL)
    {
        hashtable[hash]->words = hashtable_list_new();
    }
    hashtable_list_add(hashtable[hash]->words, word);
}

// RETURN THE A LIST CONTIANING ALL THE FILENAMES IN HASHTABLE_MLIST
LIST *hashtable_mlist_filename(HASHTABLE_MLIST *hashtable)
{
    LIST *list = list_new();
    for (uint16_t i = 0; i < HASHTABLE_MLIST_SIZE; i++)
    {
        MLIST *mlist = hashtable[i];
        while (mlist != NULL && mlist->filename != NULL)
        {
            list = list_add(list, mlist->filename);
            mlist = mlist->next;
        }
    }
    return list;
}

//  PRINT ALL OF FILENAMES IN THE HASHTABLE_MLIST
void hashtable_mlist_filename_print(HASHTABLE_MLIST *hashtable)
{
    for (uint16_t i = 0; i < HASHTABLE_MLIST_SIZE; i++)
    {
        MLIST *mlist = hashtable[i];
        mlist_filename_print(mlist);
    }
}

// CHECK IF THE FILENAME ALREADY EXISTS IN A GIVEN HASHTABLE_MLIST
bool hashtable_mlist_find(HASHTABLE_MLIST *hashtable, char *filename)
{
    uint16_t hash = DJBHash(filename) % HASHTABLE_MLIST_SIZE;

    return mlist_find(hashtable[hash], filename);
}

// RETURN THE KEYWORD LIST OF THE GIVEN FILENAME
HASHTABLE_LIST *hashtable_mlist_filename_list(HASHTABLE_MLIST *hashtable, char *filename)
{
    uint16_t hash = DJBHash(filename) % HASHTABLE_MLIST_SIZE;

    MLIST *mlist = hashtable[hash];
    if (mlist_find(mlist, filename))
    {
        while (mlist != NULL && mlist->filename != NULL && filename != NULL)
        {
            if (!strcmp(mlist->filename, filename))
            {
                return mlist->words;
            }
            mlist = mlist->next;
        }
    }
    return mlist_add(hashtable[hash], filename)->words;
}

// RETURN THE LIST OF FILENAME HAVING THE KEYWORD UNDER THEIR HASHTABLE_LIST
LIST *hashtable_mlist_files_have_word(HASHTABLE_MLIST *hashtable, char *keyword)
{
    LIST *list = list_new();
    for (uint16_t i = 0; i < HASHTABLE_MLIST_SIZE; i++)
    {
        MLIST *mlist = hashtable[i];
        while (mlist != NULL)
        {
            if (hashtable_list_find(mlist->words, keyword))
            {
                list = list_add(list, mlist->filename);
            }
            mlist = mlist->next;
        }
    }
    return list;
}

// PRINT FILENAMES HAVING THE KEYWORD UNDER THEIR WORD LIST
void hashtable_mlist_files_have_word_print(HASHTABLE_MLIST *hashtable, char *keyword)
{
    LIST *list = hashtable_mlist_files_have_word(hashtable, keyword);
    if (list == NULL || list->word == NULL)
    {
        exit(EXIT_FAILURE);
    }
    list_file_print(list);
    list_free(list);
    printf("\n");
}

// UPDATE HASHTABLE1 USING HASHTABLE2
void hashtable_mlist_update(HASHTABLE_MLIST *hashtable1, HASHTABLE_MLIST *hashtable2)
{
    for (uint16_t i = 0; i < HASHTABLE_MLIST_SIZE; i++)
    {
        MLIST *mlist1 = hashtable1[i];
        MLIST *mlist2 = hashtable2[i];
        mlist_update(mlist1, mlist2);
    }
}

//  REMOVE A MLIST HAVING GIVEN FILENAME FROM THE HASHTABLE_MLIST
void hashtable_mlist_remove(HASHTABLE_MLIST *hashtable, char *filename)
{
    filename = getRealPath(filename);
    printf("\t%s\n", filename);
    uint16_t hash = DJBHash(filename) % HASHTABLE_MLIST_SIZE;

    mlist_remove(hashtable[hash], filename);
    if (hashtable[hash]->next == NULL && hashtable[hash]->filename != NULL && filename != NULL)
    {
        if (!strcmp(hashtable[hash]->filename, filename))
        {
            hashtable[hash] = mlist_new();
        }
    }

    free(filename);
}

//  PRINT EVERYTHING IN HASHTABLE_MLIST
void hashtable_mlist_print(HASHTABLE_MLIST *hashtable)
{
    for (uint16_t i = 0; i < HASHTABLE_MLIST_SIZE; i++)
    {
        if (hashtable[i] != NULL)
        {
            mlist_print(hashtable[i]);
        }
    }
}

//  FREE THE SPACE ALLOCATED FOR A GIVEN HASHTABLE_MLIST
void hashtable_mlist_free(HASHTABLE_MLIST *hashtable)
{
    for (uint16_t i = 0; i < HASHTABLE_MLIST_SIZE; i++)
    {
        mlist_free(hashtable[i]);
        hashtable[i] = NULL;
    }
    free(hashtable);
    hashtable = NULL;
}