#define _POSIX_C_SOURCE 200112L

#include "hashtable_list.h"

// DJBHASH FUNCTION FOR HASH STRING
uint64_t DJBHash(char *string)
{
    uint64_t hash = 5381;
    int c;

    while (c = *string++)
        hash = ((hash << 5) + hash) + c;

    return hash;
}

//  ALLOCATE AND INITIALISE SPACE FOR A NEW HASHTABLE (AN ARRAY OF LISTS)
HASHTABLE_LIST *hashtable_list_new(void)
{
    HASHTABLE_LIST *new = calloc(HASHTABLE_LIST_SIZE, sizeof(LIST *));

    CHECK_MEM(new);
    return new;
} HASHTABLE_LIST;

//  ADD A NEW STRING TO A GIVEN HASHTABLE
void hashtable_list_add(HASHTABLE_LIST *hashtable, char *string)
{
    uint32_t hash = DJBHash(string) % HASHTABLE_LIST_SIZE;

    hashtable[hash] = list_add(hashtable[hash], string);
}

//  FIND OUT IF A REQUIRED STRING ALREADY EXISTS IN A GIVEN HASHTABLE
bool hashtable_list_find(HASHTABLE_LIST *hashtable, char *string)
{
    uint64_t hash = DJBHash(string) % HASHTABLE_LIST_SIZE;

    return list_find(hashtable[hash], string);
}
