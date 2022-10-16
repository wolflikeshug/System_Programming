//  CITS2002 Project 2 2022
//  Student:   23006364   HU   ZHUO   100

#ifndef _TROVEFILEIO_H
#define _TROVEFILEIO_H

#include "datastruct/hashtable_mlist.h"
#include "wordFileIO.h"

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