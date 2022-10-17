/*  
*   CITS2002  Project 2  2022-sem2
*   Student:  23006364   HU ZHUO   100
*/

#include "list.h"

// MAKE A NFW BLANK LIST ITEM
LIST *list_new(void)
{
    LIST *new = calloc(1, sizeof(LIST));
    CHECK_MEM(new);
    new->word = NULL;
    new->next = NULL;
    return new;
}

// DETERMINE IF THE TARGET IS STORED IN A GIVEN LIST
bool list_find(LIST *list, char *target)
{
    while (target != NULL && list != NULL)
    {
        if (list->word != NULL && strcmp(list->word, target) == 0)
        {
            return true;
        }
        list = list->next;
    }
    return false;
}

//  ALLOCATE SPACE FOR A NEW LIST ITEM AND CHECK IF ALLOCATION SUCCEEDS
LIST *list_new_item(char *word)
{
    LIST *newList = calloc(1, sizeof(LIST));
    CHECK_MEM(newList);
    newList->word = strdup(word);
    CHECK_MEM(newList->word);
    newList->next = list_new();
    CHECK_MEM(newList->next);
    return newList;
}

// ADD NEW CHAIN TO THE LIST, DO NOTHING IF THE CHAIN IS ALREADY IN THE LIST
LIST *list_add(LIST *list, char *word)
{
    LIST *tmp = list;
    if (list_find(list, word))
    {
        return tmp;
    }
    else
    {
        LIST *newList = list_new_item(word);
        newList->next = tmp;
        return newList;
    }
}

// REMOVE CHAIN FROM THE LIST, DO NOTHING IF THE CHAIN IS NOT IN THE LIST
void list_remove(LIST *list, char *target)
{
    while (target != NULL && list != NULL)
    {
        if (strcmp(list->word, target) == 0)
        {
            LIST *tmp = list->next;
            list->next = list->next->next;
            free(tmp);
            break;
        }
        list = list->next;
    }
}

// PRINT THE LIST
void list_print(LIST *list)
{
    while (list != NULL)
    {
        if (list->word != NULL)
        {
            printf("%s, ", list->word);
        }
        list = list->next;
    }
}

// SPECIAL list_print
void list_file_print(LIST *list)
{
    while (list != NULL)
    {
        if (list->word != NULL)
        {
            printf("%s\n", list->word);
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
        tmp = NULL;
    }
    free(list);
    list = NULL;
}