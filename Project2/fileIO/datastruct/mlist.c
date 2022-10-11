//  CITS2002 Project 2 2022
//  Student:   23006364   HU   ZHUO   100

#include "mlist.h"

// MAKE A BLANK MLIST ITEM
MLIST *mlist_new(void)
{
    MLIST *mlist = (MLIST *)malloc(sizeof(MLIST));
    CHECK_MEM(mlist);
    mlist->filename = NULL;
    mlist->words = hashtable_list_new();
    mlist->next = NULL;
    return mlist;
}

//  DETERMINE IF THE TARGET FILENAME IS STORED IN A GIVEN MLIST
bool mlist_find(MLIST *mlist, char *target)
{
    while (mlist != NULL && mlist->filename != NULL && target != NULL)
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
MLIST *mlist_new_item(char *filename)
{
    MLIST *newMList = calloc(1, sizeof(MLIST));
    CHECK_MEM(newMList);
    newMList->filename = strdup(filename);
    CHECK_MEM(newMList->filename);
    newMList->words = hashtable_list_new();
    CHECK_MEM(newMList->words);
    newMList->next = mlist_new();
    CHECK_MEM(newMList->next);
    return newMList;
}

// ADD NEW FILENAME TO THE MLIST, REPLACE IT IF THE FILENAME IS ALREADY IN THE MLIST
MLIST *mlist_add(MLIST *mlist, char *filename)
{
    if (mlist_find(mlist, filename))
    {
        return mlist;
    }
    else
    {
        MLIST *newMList = mlist_new_item(filename);
        newMList->next = mlist;
        return newMList;
    }
}

// REPLACE THE CHAIN WITH THE SAME FILENAME IN MLIST2
void mlist_replace(MLIST *mlist1, MLIST *mlist2)
{
    MLIST *tmp = mlist1;
    while (mlist1 != NULL)
    {
        if (mlist_find(mlist2, mlist1->filename))
        {
            mlist1->words = mlist2->words;
        }
        mlist1 = mlist1->next;
    }
    mlist1 = tmp;
}

// REMOVE CHAIN FROM THE MLIST, DO NOTHING IF THE FILENAME IS NOT IN THE MLIST
void mlist_remove(MLIST *mlist, char *target)
{
    while (mlist->next != NULL && mlist->filename != NULL && target != NULL)
    {
        if (strcmp(mlist->filename, target) == 0)
        {
            MLIST *tmp = mlist->next;
            mlist->next = mlist->next->next;
            free(tmp);
            break;
        }
        mlist = mlist->next;
    }
}

// Print the MLIST
void mlist_print(MLIST *mlist)
{
    if (mlist != NULL)
    {
        while (mlist->next != NULL)
        {
            if (mlist->filename != NULL)
            {
                printf("%s:\n", mlist->filename);
                hashtable_list_print(mlist->words);
                printf("\n");
            }
            mlist = mlist->next;
        }
        if (mlist->next == NULL && mlist->filename != NULL)
        {
            printf("%s:\n", mlist->filename);
            hashtable_list_print(mlist->words);
            printf("\n");
        }
    }
}

// PRINT THE FILE NAME IN THE MLIST
void mlist_filename_print(MLIST *mlist)
{
    if (mlist != NULL)
    {
        while (mlist->next != NULL)
        {
            if (mlist->filename != NULL)
            {
                printf("%s\n", mlist->filename);
            }
            mlist = mlist->next;
        }
        if (mlist->next == NULL && mlist->filename != NULL)
        {
            printf("%s\n", mlist->filename);
        }
    }
}

// FREE THE MLIST
void mlist_free(MLIST *mlist)
{
    while (mlist != NULL)
    {
        MLIST *tmp = mlist;
        free(tmp->filename);
        hashtable_list_free(mlist->words);
        mlist = mlist->next;
        free(tmp);
        tmp = NULL;
    }
    free(mlist);
    mlist = NULL;
}