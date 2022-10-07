#define _POSIX_C_SOURCE 20089L
#define _GNU_SOURCE

#include "hashtable_list.h"

//  ALLOCATE AND INITIALISE SPACE FOR A NEW HASHTABLE (AN ARRAY OF LISTS)
HASHTABLE_LIST *hashtable_list_new(void)
{
    HASHTABLE_LIST *new = calloc(HASHTABLE_LIST_SIZE, sizeof(LIST *));
    CHECK_MEM(new);
    for (int i = 0; i < HASHTABLE_LIST_SIZE; i++)
    {
        new[i] = list_new();
    }
    return new;
}

//  ADD A NEW STRING TO A GIVEN HASHTABLE
void hashtable_list_add(HASHTABLE_LIST *hashtable, char *string)
{
    uint64_t hash = DJBHash(string) % HASHTABLE_LIST_SIZE;

    hashtable[hash] = list_add(hashtable[hash], string);
}

//  FIND OUT IF A REQUIRED STRING ALREADY EXISTS IN A GIVEN HASHTABLE
bool hashtable_list_find(HASHTABLE_LIST *hashtable, char *string)
{
    uint64_t hash = DJBHash(string) % HASHTABLE_LIST_SIZE;
    
    return list_find(hashtable[hash], string);
}

// PRINT THE HASHTABLE
void hashtable_list_print(HASHTABLE_LIST *hashtable)
{
    for (int i = 0; i < HASHTABLE_LIST_SIZE; i++)
    {
        LIST *list = hashtable[i];
        if (list != NULL)
        {
            list_print(list);
        }
    }
    printf("\n");
}

// REMOVE A STRING FROM THE HASHTABLE
extern void hashtable_list_remove(HASHTABLE_LIST *hashtable, char *string)
{
    uint64_t hash = DJBHash(string) % HASHTABLE_LIST_SIZE;
    list_remove(hashtable[hash], string);
    if (hashtable[hash]->next == NULL && hashtable[hash]->keyword != NULL && string != NULL)
    {
        if (strcmp(hashtable[hash]->keyword, string) == 0)
        {
            hashtable[hash] = list_new();
        }
    }
}

// FREE THE HASHTABLE
void hashtable_list_free(HASHTABLE_LIST *hashtable)
{
    for (int i = 0; i < HASHTABLE_LIST_SIZE; i++)
    {
        list_free(hashtable[i]);
        hashtable[i] = NULL;
    }
    free(hashtable);
    hashtable = NULL;
}
