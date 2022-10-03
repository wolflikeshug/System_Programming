#define _POSIX_C_SOURCE 200112L

#include "list.h"

// CREATE A NEW, EMPTY LIST
LIST *list_new(void)
{
    return NULL;
}

//  DETERMINE IF THE TARGET IS STORED IN A GIVEN LIST
bool list_find(LIST *list, char *target)
{
    while (list != NULL)
    {
        if (strcmp(list->keyword, target) == 0)
        {
            return true;
        }
        list = list->next;
    }
    return false;
}

//  ALLOCATE SPACE FOR A NEW LIST ITEM AND CHECK IF ALLOCATION SUCCEEDS
LIST *list_new_item(char *newkeyword)
{
    LIST *newList = calloc(1, sizeof(LIST));
    CHECK_MEM(newList);
    newList->keyword = strdup(newkeyword);
    CHECK_MEM(newList->keyword);
    newList->next = list_new();
    return newList;
}

// ADD NEW CHAIN TO THE LIST, DO NOTHING IF THE CHAIN IS ALREADY IN THE LIST
LIST *list_add(LIST *list, char *newkeyword)
{
    if (list_find(list, newkeyword))
    {
        return list;
    }
    else
    {
        LIST *newList = list_new_item(newkeyword);
        newList->next = list;
        return newList;
    }
}

// REMOVE CHAIN FROM THE LIST, DO NOTHING IF THE CHAIN IS NOT IN THE LIST
void *list_remove(LIST *list, char *target)
{
    while (list->next != NULL)
    {
        if (strcmp(list->next->keyword, target) == 0)
        {
            LIST *tmp = list->next;
            list->next = list->next->next;
            free(tmp);
            break;
        }
        list = list->next;
    }
}

// FREE THE MEMORY OF THE LIST
void list_free(LIST *list)
{
    while (list != NULL)
    {
        LIST *tmp = list;
        list = list->next;
        free(tmp);
    }
}