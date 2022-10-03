#ifndef _GREBKEY_H
#define _GREBKEY_H

#include "./datastruct/hashtable_mlist.h"

#define keylen = 4

// CHECK IF THE CHAR CAN KEEP BUILDING THE KEY
extern bool stillWord(char *word);

// RECORD CHAR UNTIL IT IS NOT A WORD
extern char *recordWord(char *word);

// CHECK IF THE WORD LEN IS GREATER THAN KEYLEN 
extern bool wordlen_check(char *word);

// PUT THE WORD INTO HASHTABLE_LIST
extern void store_word(char *word, HASHTABLE_MLIST *hashtable);



#endif