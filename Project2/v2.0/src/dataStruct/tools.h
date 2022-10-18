/*  
*   CITS2002  Project 2  2022-sem2
*   Student:  23006364   HU ZHUO   100
*/

// open up all features including POSIX_C_SOURCE
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#ifndef _TOOLS_H
#define _TOOLS_H

#include <ctype.h>
#include <dirent.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <pthread.h>
#include <unistd.h>


extern uint32_t wordlen;
extern uint32_t ARG_MAX;

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
extern uint16_t DJBHash(char *string);

// CHECK IF THE STRING IS A WORD
extern bool isString(char *string);

// CHANGE THE KEYLEN
extern void change_wordlen(uint32_t len);

// CHECK IF THE WORD LEN IS GREATER THAN KEYLEN
extern bool wordlen_check(char *word);

// IF THE FILE IS EXIST RETURN THE FILE POINTER OTHERWISE POP UP ERROR MESSAGE
extern FILE *openfile(char *filename);

// GET THE REAL PATH OF THE FILE
extern char *getRealPath(char *filename);

// GET ONE LINE FROM THE FILE
extern char *getLine(FILE *file);

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