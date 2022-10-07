#ifndef _WORDFILEIO_H
#define _WORDFILEIO_H

#include "datastruct/hashtable_mlist.h"

// You may find this file is quite empty. That's because most of the functions are been moved to tools.h/tools.c

// RECORD ALL THE WORDS FROM FILE INTO THE HASHTABLE
extern void recordWord(char *filename, HASHTABLE_MLIST *hashtable);

#endif