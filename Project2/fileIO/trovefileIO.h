#ifndef _TROVEFILEIO_H
#define _TROVEFILEIO_H

#include "datastruct/hashtable_mlist.h"

extern char *TROVE_FILE;
extern FILE *TROVE_FILE_P;

// CHANGE THE TROVE FILE NAME
extern void change_trove_file(char *filename);

// OPEN THE TROVE FILE
extern void trovefile_open(void);

// CLEAR THE TROVE FILE FOR REWRITING
extern void trovefile_open_rewrite(void);

// CLOSE THE TROVE FILE
extern void trovefile_close(void);

// READ THE TROVE FILE AND LOAD THE HASHTABLE FROM IT
extern HASHTABLE_MLIST *trovefile_load(void);

// UPDATE THE HASHTABLE TO THE TROVE FILE, OVERWRITING THE OLD DATA HAVE SAME FILE NAME WHILE KEEPING THE OTHER DATA
extern void trovefile_update(HASHTABLE_MLIST *hashtbale);

// REPLACE THE TROVE FILE WITH THE NEW ONE, REMOVE THE OLD ONE AND REPLACE IT WITH THE NEW ONE
extern void trovefile_replace(HASHTABLE_MLIST *hashtable);


#endif