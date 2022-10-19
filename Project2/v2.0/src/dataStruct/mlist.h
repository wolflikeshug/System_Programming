/*
 *   CITS2002  Project 2  2022-sem2
 *   Student:  23006364   HU ZHUO   100
 */

#ifndef _MLIST_H
#define _MLIST_H

#include <stdbool.h>

#include "hashtable_list.h"

// A MOTHER LIST HAS TWO LINKS, ONE FOR A SIMPLE LIST, ONE FOR THE NEXT MOTHER LIST
typedef struct mlist
{
    char *filename;
    char *md5;
    HASHTABLE_LIST *words;
    struct mlist *next;
} MLIST;

// MAKE A BLANK MLIST ITEM
extern MLIST *mlist_new(void);

// DETERMINE IF THE TARGET FILENAME IS STORED IN A GIVEN MLIST
extern bool mlist_find(MLIST *mlist, char *target);

// ADD NEW FILENAME TO THE MLIST, DO NOTHING IF THE FILENAME IS ALREADY IN THE MLIST
extern MLIST *mlist_add(MLIST *mlist, char *filename);

// REPLACE THE CHAIN IN MLIST1 WITH THE SAME FILENAME IN MLIST2, INSERT A NEW CHAIN IF THE FILENAME IN MLIST2 IS NOT IN MLIST1
extern void mlist_update(MLIST *mlist1, MLIST *mlist2);

// REMOVE FILENAME FROM THE MLIST, DO NOTHING IF THE FILENAME IS NOT IN THE MLIST
extern void mlist_remove(MLIST *mlist, char *target);

// Print the MLIST
extern void mlist_print(MLIST *mlist);

// PRINT THE FILE NAME IN THE MLIST
extern void mlist_filename_print(MLIST *mlist);

// FREE THE MEMORY OF THE MLIST
extern void mlist_free(MLIST *mlist);

#endif