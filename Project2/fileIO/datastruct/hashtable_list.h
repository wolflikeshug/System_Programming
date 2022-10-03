#ifndef _HASHTABLE_LIST_H
#define _HASHTABLE_LIST_H

#include "list.h"

#define HASHTABLE_LIST_SIZE 997

//  WE DEFINE A HASHTABLE AS A (WILL BE, DYNAMICALLY ALLOCATED) ARRAY OF LISTs
typedef LIST *HASHTABLE_LIST;

// DJBHASH FUNCTION FOR HASH STRING
extern uint64_t DJBHash(char *string);

//  ALLOCATE SPACE FOR A NEW HASHTABLE (AND ARRAY OF LISTS)
extern HASHTABLE_LIST *hashtable_list_new(void);

//  ADD NEW STRING TO A GIVEN HASHTABLE
extern void hashtable_list_add(HASHTABLE_LIST *hashtable, char *string);

//  FIND OUT IF A REQUIRED STRING ALREADY EXISTS IN A GIVEN HASHTABLE
extern bool hashtable_list_find(HASHTABLE_LIST *hashtable, char *string);

#endif