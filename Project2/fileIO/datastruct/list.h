#ifndef _LIST_H
#define _LIST_H

#include "tools.h"

// A SIMPLE LIST IMPLEMENTATION
typedef struct list
{
    char *keyword;
    struct list *next;
} LIST;

// MAKE A BLANK LIST ITEM
extern LIST *list_new(void);

// DETERMINE IF THE TARGET IS STORED IN A GIVEN LIST
extern bool list_find(LIST *list, char *target);

// ADD NEW CHAIN TO THE LIST, DO NOTHING IF THE CHAIN IS ALREADY IN THE LIST
extern LIST *list_add(LIST *list, char *newkeyword);

// REMOVE CHAIN FROM THE LIST, DO NOTHING IF THE CHAIN IS NOT IN THE LIST
extern void list_remove(LIST *list, char *target);

#endif