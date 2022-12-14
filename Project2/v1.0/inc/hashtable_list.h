/*
 *   CITS2002  Project 2  2022-sem2
 *   Student:  23006364   HU ZHUO   100
 */

#ifndef _HASHTABLE_LIST_H
#define _HASHTABLE_LIST_H

#include "list.h"

/* The following include does nothing,
 *  These header files are included here just to show
 *  some of the functions/datatype are using
 *  are declared in the corresponding header file
 *  Because there is protection setted in every header file,
 *  it is safe to include them multiple times
 *  without causing muitiple inclusion error
 *  it is fine to remove them if you want
 */

#include "tools.h"
#include "list.h"

#define HASHTABLE_LIST_SIZE 2027

/*
 *   Implementation of a hashtable using a list
 *   This is the unit to store all the words gets from single file
 */

// WE DEFINE A HASHTABLE AS A (WILL BE, DYNAMICALLY ALLOCATED) ARRAY OF LISTs
typedef LIST *HASHTABLE_LIST;

// ALLOCATE SPACE AND INITIALISE A NEW HASHTABLE_LIST
extern HASHTABLE_LIST *hashtable_list_new(void);

// ADD NEW STRING TO A GIVEN HASHTABLE_LIST
extern void hashtable_list_add(HASHTABLE_LIST *hashtable, char *string);

// CHECK IF A REQUIRED STRING ALREADY EXISTS IN THE GIVEN HASHTABLE_LIST
extern bool hashtable_list_find(HASHTABLE_LIST *hashtable, char *string);

// PRINT THE HASHTABLE_LIST
extern void hashtable_list_print(HASHTABLE_LIST *hashtable);

// REMOVE A STRING FROM THE HASHTABLE_LIST
extern void hashtable_list_remove(HASHTABLE_LIST *hashtable, char *string);

// FREE THE HASHTABLE_LIST
extern void hashtable_list_free(HASHTABLE_LIST *hashtable);

#endif