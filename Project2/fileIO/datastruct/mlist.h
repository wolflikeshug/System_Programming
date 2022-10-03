#ifndef _MLIST_H
#define _MLIST_H

#include <stdbool.h>

#include "hashtable_list.h"

// A MOTHER LIST HAS TWO LINKS, ONE FOR A SIMPLE LIST, ONE FOR THE NEXT MOTHER LIST
typedef struct mlist
{
    char *filename;
    HASHTABLE_LIST*keys;
    struct mlist *next;
} MLIST;

// MAKE A BLANK MLIST ITEM
extern MLIST *mlist_new(void);

// DETERMINE IF THE TARGET FILENAME IS STORED IN A GIVEN MLIST
extern bool mlist_find(MLIST *mlist, char *target);

// ADD NEW FILENAME TO THE MLIST, DO NOTHING IF THE FILENAME IS ALREADY IN THE MLIST
extern MLIST *mlist_add(MLIST *mlist, char *newfilename);

// REPLACE THE CHAIN WITH THE SAME FILENAME IN MLIST2
extern void mlist_replace(MLIST *mlist1, MLIST *mlist2);

// REMOVE FILENAME FROM THE MLIST, DO NOTHING IF THE FILENAME IS NOT IN THE MLIST
extern void *mlist_remove(MLIST *mlist, char *target);

#endif