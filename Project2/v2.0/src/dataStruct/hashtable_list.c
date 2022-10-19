/*  
*   CITS2002  Project 2  2022-sem2
*   Student:  23006364   HU ZHUO   100
*/

#include "hashtable_list.h"

// ALLOCATE SPACE AND INITIALISE A NEW HASHTABLE_LIST
HASHTABLE_LIST *hashtable_list_new(void)
{
    HASHTABLE_LIST *new = (HASHTABLE_LIST *)calloc(HASHTABLE_LIST_SIZE, sizeof(LIST *));
    CHECK_MEM(new);
    
    for (uint16_t i = 0; i < HASHTABLE_LIST_SIZE; i++)
    {
        new[i] = list_new();
    }
    return new;
}

// ADD A NEW STRING TO A GIVEN HASHTABLE_LIST
void hashtable_list_add(HASHTABLE_LIST *hashtable, char *string)
{
    uint16_t hash = DJBHash(string) % HASHTABLE_LIST_SIZE;

    hashtable[hash] = list_add(hashtable[hash], string);
}

// CHECK IF A REQUIRED STRING ALREADY EXISTS IN THE GIVEN HASHTABLE_LIST
bool hashtable_list_find(HASHTABLE_LIST *hashtable, char *string)
{
    uint16_t hash = DJBHash(string) % HASHTABLE_LIST_SIZE;

    return list_find(hashtable[hash], string);
}

// PRINT THE HASHTABLE_LIST
void hashtable_list_print(HASHTABLE_LIST *hashtable)
{
    for (uint16_t i = 0; i < HASHTABLE_LIST_SIZE; i++)
    {
        LIST *list = hashtable[i];
        if (list != NULL)
        {
            list_print(list);
        }
    }
    printf("\n");
}

// REMOVE A STRING FROM THE HASHTABLE_LIST
extern void hashtable_list_remove(HASHTABLE_LIST *hashtable, char *string)
{
    uint16_t hash = DJBHash(string) % HASHTABLE_LIST_SIZE;
    list_remove(hashtable[hash], string);
    if (hashtable[hash]->next == NULL && hashtable[hash]->word != NULL && string != NULL)
    {
        if (!strcmp(hashtable[hash]->word, string))
        {
            hashtable[hash] = list_new();
        }
    }
}

// FREE THE HASHTABLE_LIST
void hashtable_list_free(HASHTABLE_LIST *hashtable)
{
    for (uint16_t i = 0; i < HASHTABLE_LIST_SIZE; i++)
    {
        list_free(hashtable[i]);
        hashtable[i] = NULL;
    }
    free(hashtable);
    hashtable = NULL;
}
