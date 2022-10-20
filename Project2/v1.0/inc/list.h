/*
 *   CITS2002  Project 2  2022-sem2
 *   Student:  23006364   HU ZHUO   100
 */

#ifndef _LIST_H
#define _LIST_H

#include "tools.h"

/*
 *  This is a implementation of a linked list
 *  which is the smallest unit to store one word
 */

// IMPLITATION OF LIST
typedef struct list
{
    char *word;
    struct list *next;
} LIST;

// MAKE A NFW BLANK LIST ITEM
extern LIST *list_new(void);

// DETERMINE IF THE TARGET IS STORED IN A GIVEN LIST
extern bool list_find(LIST *list, char *target);

// ADD NEW CHAIN TO THE LIST, DO NOTHING IF THE CHAIN IS ALREADY IN THE LIST
extern LIST *list_add(LIST *list, char *word);

// REMOVE CHAIN FROM THE LIST, DO NOTHING IF THE CHAIN IS NOT IN THE LIST
extern void list_remove(LIST *list, char *target);

// PRINT THE LIST
extern void list_print(LIST *list);

// SPECIAL list_print (ONLY USED FOR TESTING)
extern void list_file_print(LIST *list);

// FREE THE MEMORY OF THE LIST
extern void list_free(LIST *list);

#endif