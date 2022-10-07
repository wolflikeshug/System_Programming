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
#include <zlib.h>

extern int keylen;

// CHECK IF THE MEMORY ALLOCATION WAS SUCCESSFUL
#define CHECK_MEM(p) if(p == NULL) { perror(__func__); exit(EXIT_FAILURE); }

// DJBHASH FUNCTION FOR HASH STRING
extern uint64_t DJBHash(char *string);

// GET THE FILE SIZE OF THE TROVE FILE
extern int file_getsize(FILE * file);

// CHECK IF THE CHAR CAN KEEP BUILDING THE KEY
extern bool stillWord(char word);

// CHANGE THE KEYLEN
extern void change_keylen(int len);

// CHECK IF THE WORD LEN IS GREATER THAN KEYLEN
extern bool wordlen_check(char *word);

// IF THE FILE IS NOT EXIST POP UP ERROR MESSAGE
// IF THE FILE IS EXIST RETURN THE FILE POINTER
extern FILE *openfile(char *filename);

// CHECK IF THE FILE IS EXIST, IF EXIST DO NOTHING IF NOT EXIT POP ERROR MESSAGE
extern void file_exist(char *filename);

// GET THE REAL PATH OF THE FILE
extern char *getRealPath(char *filename);

// GET ONE LINE FROM THE FILE DINAMICALLY FROM A ZIPPED FILE USING ZCAT
extern char *getLine(FILE *file);

#endif