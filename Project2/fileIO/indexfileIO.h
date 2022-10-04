#ifndef _INDEXFILEIO_H
#define _INDEXFILEIO_H

#include "datastruct/hashtable_mlist.h"

extern char *INDEX_FILE;

// CHANGE THE INDEX FILE NAME
extern void change_index_file(char *filename);

// CREATE A NEW INDEX FILE IF THERE ISN'T ONE ALREADY, OTHERWISE OPEN IT
extern FILE *indexfile_init(void);   

// READ THE INDEX FILE AND LOAD THE HASHTABLE FROM IT
extern void indexfile_load(FILE *indexfile, HASHTABLE_MLIST *hashtable);

// UPDATE THE HASHTABLE TO THE INDEX FILE, OVERWRITING THE OLD DATA HAVE SAME FILE NAME WHILE KEEPING THE OTHER DATA
extern void indexfile_update(FILE *indexFile, HASHTABLE_MLIST *hashtbale);

// REPLACE THE INDEX FILE WITH THE NEW ONE, REMOVE THE OLD ONE AND REPLACE IT WITH THE NEW ONE
extern void indexfile_replace(FILE *indexFile, HASHTABLE_MLIST *hashtable);

// CLOSE THE INDEX FILE
extern void indexfile_close(FILE *indexFile);

#endif