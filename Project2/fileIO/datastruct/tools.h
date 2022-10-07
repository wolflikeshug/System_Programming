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
#include <sys/stat.h>

extern int keylen;
extern int ARG_MAX;

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

// CHECK IF THE FILE IS EXIST RETURN TRUE IF THE FILE IS EXIST
extern bool file_exist(char *filename);

// GET THE REAL PATH OF THE FILE
extern char *getRealPath(char *filename);

// GET ONE LINE FROM THE FILE DINAMICALLY
extern char *getLine(FILE *file);

// CREATE ONE NEW FILE UNDER A SECRET DIR WITH GIVEN FILENAME AND FILLED WITH GIVEN CONTENT
extern void createFile(char *filename, char *content);

// REMOVE THE GIVEN FILE
extern void removeFile(char *filename);

// REMOVE THE GIVEN DIR
extern void removeDir(char *dirname);

// A FUNCTION CHANGE THE GIVEN INT TO STRING
extern char *itoa(int num);

// CHECK IF THE GIVEN STRING IS A INTERGER
extern bool isNumber(char *str);

// CHECK IF THE GIVEN NAME IS A FILE
extern bool isFile(char *name);

#endif