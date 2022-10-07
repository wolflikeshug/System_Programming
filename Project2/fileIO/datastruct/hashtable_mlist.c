#define _POSIX_C_SOURCE 20089L
#define _GNU_SOURCE

#include "hashtable_mlist.h"

//  ALLOCATE AND INITIALISE SPACE FOR A NEW HASHTABLE (AN ARRAY OF MLISTS)
HASHTABLE_MLIST *hashtable_mlist_new(void)
{
    HASHTABLE_MLIST *new = calloc(HASHTABLE_MLIST_SIZE, sizeof(MLIST *));
    CHECK_MEM(new);
    for (int i = 0; i < HASHTABLE_MLIST_SIZE; i++)
    {
        new[i] = mlist_new();
    }
    return new;
}

//  ADD A NEW WORD TO THE FILENAME'S MLIST
void hashtable_mlist_add(HASHTABLE_MLIST *hashtable, char *filename, char *word)
{
    uint64_t hash = DJBHash(filename) % HASHTABLE_MLIST_SIZE;

    hashtable[hash] = mlist_add(hashtable[hash], filename);
    if (hashtable[hash]->keys == NULL)
    {
        hashtable[hash]->keys = hashtable_list_new();
    }
    hashtable_list_add(hashtable[hash]->keys, word);
}

//  DETERMINE IF A REQUIRED STRING ALREADY EXISTS IN A GIVEN HASHTABLE
bool hashtable_mlist_find(HASHTABLE_MLIST *hashtable, char *filename)
{
    uint64_t hash = DJBHash(filename) % HASHTABLE_MLIST_SIZE;

    return mlist_find(hashtable[hash], filename);
}

// RETURN THE KEYWORD LIST OF THE GIVEN FILENAME IF NOT FOUND CREATE A NEW ONE
HASHTABLE_LIST *hashtable_mlist_filename_list(HASHTABLE_MLIST *hashtable, char *filename)
{
    uint64_t hash = DJBHash(filename) % HASHTABLE_MLIST_SIZE;

    MLIST *mlist = hashtable[hash];
    if (mlist_find(mlist, filename))
    {
        while (mlist != NULL && mlist->filename != NULL)
        {
            if (strcmp(mlist->filename, filename) == 0)
            {
                return mlist->keys;
            }
            mlist = mlist->next;
        }
    }
    return mlist_add(hashtable[hash], filename)->keys;
}

//  RETURN THE LIST OF FILENAME HAVING THE KEYWORD UNDER THEIR HASHTABLE_LIST
LIST *hashtable_mlist_have_key(HASHTABLE_MLIST *hashtable, char *keyword)
{
    LIST *list = list_new();
    for (int i = 0; i < HASHTABLE_MLIST_SIZE; i++)
    {
        MLIST *mlist = hashtable[i];
        while (mlist != NULL)
        {
            if (hashtable_list_find(mlist->keys, keyword))
            {
                list = list_add(list, mlist->filename);
            }
            mlist = mlist->next;
        }
    }
    return list;
}

//  PRINT LIST OF FILENAME HAVING THE KEYWORD UNDER THEIR HASHTABLE_LIST
void hashtable_mlist_have_key_print(HASHTABLE_MLIST *hashtable, char *key)
{
    LIST *list = hashtable_mlist_have_key(hashtable, key);
    list_file_print(list);
    list_free(list);
}

// TRAVERSE THE HASHTABLE1 AND UPDATE THE CHAIN WITH THE SAME FILENAME IN HASHTABLE2
void hashtable_mlist_update(HASHTABLE_MLIST *hashtable1, HASHTABLE_MLIST *hashtable2)
{
    for (int i = 0; i < HASHTABLE_MLIST_SIZE; i++)
    {
        MLIST *list = hashtable1[i];
        while (list != NULL)
        {
            if (hashtable_mlist_find(hashtable2, list->filename))
            {
                mlist_replace(list, hashtable2[i]);
            }
            else
            {
                list->next = hashtable2[i];
            }
            list = list->next;
        }
    }
}

//  REMOVE A STRING FROM A GIVEN HASHTABLE
void hashtable_mlist_remove(HASHTABLE_MLIST *hashtable, char *filename)
{
    uint64_t hash = DJBHash(filename) % HASHTABLE_MLIST_SIZE;

    mlist_remove(hashtable[hash], filename);
    if (hashtable[hash]->next == NULL)
    {
        printf("%s ?= %s\n", hashtable[hash]->filename, filename);
        if (strcmp(hashtable[hash]->filename, filename) == 0)
        {
            hashtable[hash] = mlist_new();
        }
    }
}

//  Print the hashtable
void hashtable_mlist_print(HASHTABLE_MLIST *hashtable)
{
    for (int i = 0; i < HASHTABLE_MLIST_SIZE; i++)
    {
        if (hashtable[i] != NULL)
        {
            mlist_print(hashtable[i]);
        }
    }
}

//  FREE THE SPACE ALLOCATED FOR A GIVEN HASHTABLE
void hashtable_mlist_free(HASHTABLE_MLIST *hashtable)
{
    for (int i = 0; i < HASHTABLE_MLIST_SIZE; i++)
    {
        mlist_free(hashtable[i]);
        hashtable[i] = NULL;
    }
    free(hashtable);
    hashtable = NULL;
}