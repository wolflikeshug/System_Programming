/*
 *   CITS2002  Project 2  2022-sem2
 *   Student:  23006364   HU ZHUO   100
 */

#ifndef _TROVEFILEIO_H
#define _TROVEFILEIO_H

#include "wordFileIO.h"

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
#include "mlist.h"
#include "hashtable_mlist.h"

/*
 *   Including all the operation needed to work trove-file!
 */

extern char *TROVE_FILE;
extern FILE *TROVE_FILE_P;

// CHANGE THE TROVE FILE NAME
extern void change_trove_file(char *filename);

// READ THE TROVE FILE AND LOAD THE HASHTABLE FROM IT
extern HASHTABLE_MLIST *trovefile_load(void);

// REPLACE THE TROVE FILE WITH THE NEW ONE, REMOVE THE OLD ONE AND REPLACE IT WITH THE NEW ONE
extern void trovefile_write(HASHTABLE_MLIST *hashtable);

// UPDATE THE HASHTABLE TO THE TROVE FILE, OVERWRITING THE OLD DATA HAVE SAME FILE NAME WHILE KEEPING THE OTHER DATA
extern void trovefile_update(HASHTABLE_MLIST *hashtbale);

// PRINT ALL THE FILENAME IN THE TROVE FILE
extern void trovefile_print(void);

// PRINT ALL THE FILENAME IN THE TROVE FILE
extern void trovefile_filename_print(void);

#endif