//  CITS2002 Project 2 2022
//  Student:   23006364   HU   ZHUO   100

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE
#endif

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

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

extern int wordlen;
extern int ARG_MAX;

// CHECK IF THE MEMORY ALLOCATION WAS SUCCESSFUL
#ifndef CHECK_MEM
#define CHECK_MEM(p)        \
    if (p == NULL)          \
    {                       \
        perror(__func__);   \
        exit(EXIT_FAILURE); \
    }
#endif

// DJBHASH FUNCTION FOR HASHING STRING
extern uint64_t DJBHash(char *string);

// CHECK IF THE CHAR CAN BUILDING A WORD
extern bool isWord(char c);

// CHECK IF THE STRING IS A WORD
extern bool isString(char *string);

// CHANGE THE KEYLEN
extern void change_wordlen(int len);

// CHECK IF THE WORD LEN IS GREATER THAN KEYLEN
extern bool wordlen_check(char *word);

// IF THE FILE IS NOT EXIST POP UP ERROR MESSAGE
// IF THE FILE IS EXIST RETURN THE FILE POINTER
extern FILE *openfile(char *filename);

// CHECK IF THE FILE IS EXIST RETURN TRUE IF THE FILE IS EXIST
extern bool file_exist(char *filename);

// GET THE REAL PATH OF THE FILE
extern char *getRealPath(char *filename);

// GET ONE LINE FROM THE FILE
extern char *getLine(FILE *file);

// A FUNCTION CHANGE THE GIVEN INT TO STRING
extern char *itoa(int num);

// CHECK IF THE GIVEN STRING IS A INTERGER
extern bool isInt(char *str);

// CHECK IF THE GIVEN NAME IS A FILE
extern bool isFile(char *name);

// CHECK IF THE GIVEN NAME IS DIRECTORY
extern bool isDirectory(char *name);

// CALCULATE MD5 HASH OF THE GIVEN FILE
extern char *md5sum(char *filename);

// CHECK IF THE STORED MD5 HASH IS THE SAME AS THE MD5 HASH OF THE FILE
extern bool md5check(char *md5, char *filename);

#endif