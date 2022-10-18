/*  
*   CITS2002  Project 2  2022-sem2
*   Student:  23006364   HU ZHUO   100
*/

#ifndef _WORDFILEIO_H
#define _WORDFILEIO_H

#include "../dataStruct/hashtable_mlist.h"

/* The following include does nothing, 
*  These header files are included here just to show 
*  some of the functions/datatype are using
*  are declared in the corresponding header file
*  Because there is protection setted in every header file,
*  it is safe to include them multiple times 
*  without causing muitiple inclusion error
*  it is fine to remove them if you want
*/

#include "../dataStruct/tools.h"
#include "../dataStruct/hashtable_mlist.h"
#include "trovefileIO.h"

typedef struct wordIO_thread_data 
{
    char *filename;
    HASHTABLE_MLIST *hashtable;
} WORDIO_THREAD_DATA;

// RECORD ALL THE WORDS FROM FILE INTO THE HASHTABLE
extern void *recordWord(void *thread_data);

#endif