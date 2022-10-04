#ifndef _WORDFILEIO_H
#define _WORDFILEIO_H

#include "datastruct/hashtable_mlist.h"

// RECORD ALL THE WORDS FROM FILE INTO THE HASHTABLE
extern void recordWord(FILE *fp, char *filename, HASHTABLE_MLIST *hashtable);


#endif