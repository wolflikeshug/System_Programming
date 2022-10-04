#ifndef _TOOLS_H
#define _TOOLS_H

#include <dirent.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <ctype.h>

extern int keylen;

// CHECK IF THE MEMORY ALLOCATION WAS SUCCESSFUL
#define CHECK_MEM(p) if(p == NULL) { perror(__func__); exit(EXIT_FAILURE); }

// DJBHASH FUNCTION FOR HASH STRING
extern uint64_t DJBHash(char *string);

// GET THE FILE SIZE OF THE INDEX FILE
extern int file_getsize(FILE * file);

// CHECK IF THE CHAR CAN KEEP BUILDING THE KEY
extern bool stillWord(char word);

// CHANGE THE KEYLEN
extern void change_keylen(int len);

// CHECK IF THE WORD LEN IS GREATER THAN KEYLEN
extern bool wordlen_check(char *word);

#endif