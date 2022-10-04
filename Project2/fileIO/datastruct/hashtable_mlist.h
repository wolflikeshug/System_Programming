#ifndef _HASHTABLE_MLIST_H
#define _HASHTABLE_MLIST_H

#include "mlist.h"

#define HASHTABLE_MLIST_SIZE 2027

typedef MLIST *HASHTABLE_MLIST;

//  ALLOCATE AND INITIALISE SPACE FOR A NEW HASHTABLE (AN ARRAY OF MLISTS)
extern HASHTABLE_MLIST *hashtable_mlist_new(void);

//  ADD NEW STRING TO A GIVEN HASHTABLE
extern void hashtable_mlist_add(HASHTABLE_MLIST *hashtable, char *string);

//  FIND OUT IF A REQUIRED STRING ALREADY EXISTS IN A GIVEN HASHTABLE
extern bool hashtable_mlist_find(HASHTABLE_MLIST *hashtable, char *string);

// RETURN THE KEYWORD LIST OF THE GIVEN FILENAME
extern HASHTABLE_LIST *hashtable_mlist_filename_list(HASHTABLE_MLIST *hashtable, char *filename);

//  RETURN THE LIST OF FILENAME HAVING THE KEYWORD UNDER THEIR HASHTABLE_LIST
extern LIST *hashtable_mlist_have_key(HASHTABLE_MLIST *hashtable, char *key);

// TRAVERSE THE HASHTABLE1 AND UPDATE THE CHAIN WITH THE SAME FILENAME IN HASHTABLE2
extern void hashtable_mlist_update(HASHTABLE_MLIST *hashtable1, HASHTABLE_MLIST *hashtable2);

//  REMOVE A STRING FROM A GIVEN HASHTABLE
extern void hashtable_mlist_remove(HASHTABLE_MLIST *, char *string);

#endif