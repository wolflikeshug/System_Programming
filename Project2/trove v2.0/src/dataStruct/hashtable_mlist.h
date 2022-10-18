/*  
*   CITS2002  Project 2  2022-sem2
*   Student:  23006364   HU ZHUO   100
*/

#ifndef _HASHTABLE_MLIST_H
#define _HASHTABLE_MLIST_H

#include "mlist.h"

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
#include "hashtable_list.h"

#define HASHTABLE_MLIST_SIZE 997

typedef MLIST *HASHTABLE_MLIST;

// ALLOCATE SPACE AND INITIALISE A NEW HASHTABLE_MLIST
extern HASHTABLE_MLIST *hashtable_mlist_new(void);

// ADD NEW FILENAME TO THE HASHTABLE_MLIST
extern void hashtable_mlist_add(HASHTABLE_MLIST *hashtable, char *filename, char *word);

// RETURN THE A LIST CONTIANING ALL THE FILENAMES IN HASHTABLE_MLIST
extern LIST *hashtable_mlist_filename(HASHTABLE_MLIST *hashtable);

//  PRINT ALL OF FILENAMES IN THE HASHTABLE_MLIST
extern void hashtable_mlist_filename_print(HASHTABLE_MLIST *hashtable);

// RETURN THE KEYWORD LIST OF THE GIVEN FILENAME
extern HASHTABLE_LIST *hashtable_mlist_filename_list(HASHTABLE_MLIST *hashtable, char *filename);

// PRINT FILENAMES HAVING THE KEYWORD UNDER THEIR WORD LIST
extern void hashtable_mlist_files_have_word_print(HASHTABLE_MLIST *hashtable, char *keyword);

// UPDATE HASHTABLE1 USING HASHTABLE2
extern void hashtable_mlist_update(HASHTABLE_MLIST *hashtable1, HASHTABLE_MLIST *hashtable2);

//  REMOVE A MLIST HAVING GIVEN FILENAME FROM THE HASHTABLE_MLIST
extern void hashtable_mlist_remove(HASHTABLE_MLIST *, char *filename);

//  PRINT EVERYTHING IN HASHTABLE_MLIST
extern void hashtable_mlist_print(HASHTABLE_MLIST *hashtable);

//  FREE THE SPACE ALLOCATED FOR A GIVEN HASHTABLE_MLIST
extern void hashtable_mlist_free(HASHTABLE_MLIST *hashtable);

#endif