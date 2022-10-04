#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <string.h>

#include "mlist.h"

// MAKE A BLANK MLIST ITEM
MLIST *mlist_new(void)
{
    return NULL;
}

//  DETERMINE IF THE TARGET FILENAME IS STORED IN A GIVEN MLIST
bool mlist_find(MLIST *mlist, char *target)
{
    while (mlist != NULL)
    {
        if (strcmp(mlist->filename, target) == 0)
        {
            return true;
        }
        mlist = mlist->next;
    }
    return false;
}

//  ALLOCATE SPACE FOR A NEW MLIST ITEM AND CHECK IF ALLOCATION SUCCEEDS
MLIST *mlist_new_item(char *newfilename)
{
    MLIST *newMList = calloc(1, sizeof(MLIST));
    CHECK_MEM(newMList);
    newMList->filename = strdup(newfilename);
    CHECK_MEM(newMList->filename);
    newMList->keys = list_new();
    newMList->next = mlist_new();
    return newMList;
}

// ADD NEW FILENAME TO THE MLIST, REPLACE IT IF THE FILENAME IS ALREADY IN THE MLIST
MLIST *mlist_add(MLIST *mlist, char *newfilename)
{
    if (mlist_find(mlist, newfilename))
    {
        return mlist;
    }
    MLIST *newMList = mlist_new_item(newfilename);
    newMList->next = mlist;
    return newMList;
}

// REPLACE THE CHAIN WITH THE SAME FILENAME IN MLIST2
MLIST *mlist_replace(MLIST *mlist1, MLIST *mlist2)
{
    MLIST *tmp = mlist1;
    while (mlist1 != NULL)
    {
        if (mlist_find(mlist2, mlist1->filename))
        {
            mlist1->keys = mlist2->keys;
        }
        mlist1 = mlist1->next;
    }
    return tmp;
}

// REMOVE CHAIN FROM THE MLIST, DO NOTHING IF THE FILENAME IS NOT IN THE MLIST
void *mlist_remove(MLIST *mlist, char *target)
{
    while (mlist->next != NULL)
    {
        if (strcmp(mlist->next->filename, target) == 0)
        {
            MLIST *tmp = mlist->next;
            mlist->next = mlist->next->next;
            free(tmp);
            break;
        }
        mlist = mlist->next;
    }
}

// FREE THE MLIST
void mlist_free(MLIST *mlist)
{
    while (mlist != NULL)
    {
        MLIST *tmp = mlist;
        mlist = mlist->next;
        free(tmp);
    }
}