#define _POSIX_C_SOURCE 200112L

#include "hashtable_mlist.h"

//  ALLOCATE AND INITIALISE SPACE FOR A NEW HASHTABLE (AN ARRAY OF MLISTS)
HASHTABLE_MLIST *hashtable_mlist_file(void)
{
    HASHTABLE_MLIST *new = calloc(HASHTABLE_MLIST_SIZE, sizeof(MLIST *));

    CHECK_MEM(new);
    return new;
} 

//  ADD A NEW STRING TO A GIVEN HASHTABLE
void hashtable_mlist_add(HASHTABLE_MLIST *hashtable, char *string)
{
    uint64_t hash = DJBHash(string) % HASHTABLE_MLIST_SIZE;

    hashtable[hash] = mlist_add(hashtable[hash], string);
}

//  DETERMINE IF A REQUIRED STRING ALREADY EXISTS IN A GIVEN HASHTABLE
bool hashtable_mlist_find(HASHTABLE_MLIST *hashtable, char *string)
{
    uint64_t hash = DJBHash(string) % HASHTABLE_MLIST_SIZE;

    return mlist_find(hashtable[hash], string);
}

//  RETURN THE LIST OF FILENAME HAVING THE KEYWORD UNDER THEIR HASHTABLE_LIST
LIST *hashtable_mlist_find_key(HASHTABLE_MLIST *hashtable, char *keyword)
{
    LIST *list = list_new();
    for (int i = 0; i < HASHTABLE_MLIST_SIZE; i++)
    {
        if (list != NULL)
        {
            if (hashtable_list_find(hashtable[i]->keys, keyword))
            {
                list = list_add(list, hashtable[i]->filename);
            }
        }
    }
    return list;
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
void hashtable_mlist_remove(HASHTABLE_MLIST *hashtable, char *string)
{
    uint64_t hash = DJBHash(string) % HASHTABLE_MLIST_SIZE;

    hashtable[hash] = mlist_remove(hashtable[hash], string);
}