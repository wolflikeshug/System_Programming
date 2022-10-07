#ifndef _HASHTABLE_MLIST_H
#define _HASHTABLE_MLIST_H

#include "mlist.h"

#define HASHTABLE_MLIST_SIZE 997

typedef MLIST *HASHTABLE_MLIST;

//  ALLOCATE AND INITIALISE SPACE FOR A NEW HASHTABLE (AN ARRAY OF MLISTS),.,.
extern HASHTABLE_MLIST *hashtable_mlist_new(void);

//  ADD NEW STRING TO A GIVEN HASHTABLE,.,.
extern void hashtable_mlist_add(HASHTABLE_MLIST *hashtable, char *filename, char *word);

//  FIND OUT IF A REQUIRED STRING ALREADY EXISTS IN A GIVEN HASHTABLE,.,.
extern bool hashtable_mlist_find(HASHTABLE_MLIST *hashtable, char *filename);

// RETURN THE KEYWORD LIST OF THE GIVEN FILENAME,.,.
extern HASHTABLE_LIST *hashtable_mlist_filename_list(HASHTABLE_MLIST *hashtable, char *filename);

//  RETURN THE LIST OF FILENAMES IN THE HASHTABLE
extern LIST *hashtable_mlist_files(HASHTABLE_MLIST *hashtable);

//  RETURN THE LIST OF FILENAME HAVING THE KEYWORD UNDER THEIR HASHTABLE_LIST,.,.
extern LIST *hashtable_mlist_files_have_key(HASHTABLE_MLIST *hashtable, char *key);

//  PRINT LIST OF FILENAME HAVING THE KEYWORD UNDER THEIR HASHTABLE_LIST,.,.
extern void hashtable_mlist_files_have_key_print(HASHTABLE_MLIST *hashtable, char *key);

// TRAVERSE THE HASHTABLE1 AND UPDATE THE CHAIN WITH THE SAME FILENAME IN HASHTABLE2,.,.
extern void hashtable_mlist_update(HASHTABLE_MLIST *hashtable1, HASHTABLE_MLIST *hashtable2);

//  REMOVE A FILE FROM THE GIVEN HASHTABLE,.,.
extern void hashtable_mlist_remove(HASHTABLE_MLIST *, char *filename);

//  Print the hashtable,.,.
extern void hashtable_mlist_print(HASHTABLE_MLIST *hashtable);

//  FREE THE SPACE ALLOCATED FOR A GIVEN HASHTABLE,.,.
extern void hashtable_mlist_free(HASHTABLE_MLIST *hashtable);

#endif