#define _POSIX_C_SOURCE 20089L
#define _GNU_SOURCE

#include "list.h"

// CREATE A NEW, EMPTY LIST
LIST *list_new(void)
{
    LIST *new = calloc(1, sizeof(LIST));
    CHECK_MEM(new);
    new->keyword = NULL;
    new->next = NULL;
    return new;
}

//  DETERMINE IF THE TARGET IS STORED IN A GIVEN LIST
bool list_find(LIST *list, char *target)
{
    while (list != NULL && list->keyword != NULL && target != NULL)
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
    CHECK_MEM(newList->next);
    return newList;
}

// ADD NEW CHAIN TO THE LIST, DO NOTHING IF THE CHAIN IS ALREADY IN THE LIST
LIST *list_add(LIST *list, char *newkeyword)
{
    LIST * tmp = list;
    if (list_find(list, newkeyword))
    {
        return tmp;
    }
    else
    {
        LIST *newList = list_new_item(newkeyword);
        newList->next = tmp;
        return newList;
    }
}

// REMOVE CHAIN FROM THE LIST, DO NOTHING IF THE CHAIN IS NOT IN THE LIST
void list_remove(LIST *list, char *target)
{
    while (list->next != NULL && list->next->keyword != NULL && target != NULL)
    {
        if (strcmp(list->keyword, target) == 0)
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
    if (list != NULL)
    {
        while (list->next != NULL)
        {
            if(list->keyword != NULL)
            {
                printf("%s, ", list->keyword);
            }
            list = list->next;
        }
        if (list->next == NULL)
        {
            if(list->keyword != NULL)
            {
                printf("%s, ", list->keyword);
            }
        }
    }
}

// SPECIAL PRINT FUNCTION FOR FILELIST
void list_file_print(LIST *list)
{
    if (list != NULL)
    {
        while (list->next != NULL)
        {
            if(list->keyword != NULL)
            {
                printf("%s\n", list->keyword);
            }
            list = list->next;
        }
        if (list->next == NULL)
        {
            if(list->keyword != NULL)
            {
                printf("%s\n", list->keyword);
            }
        }
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