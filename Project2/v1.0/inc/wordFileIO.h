/*
 *   CITS2002  Project 2  2022-sem2
 *   Student:  23006364   HU ZHUO   100
 */

#ifndef _WORDFILEIO_H
#define _WORDFILEIO_H

#include "hashtable_mlist.h"

/* The following include does nothing,
 *  These header files are included here just to show
 *  some of the functions/datatype are using
 *  are declared in the corresponding header file
 *  Because there is protection setted in every header file,
 *  it is safe to include them multiple times
 *  without causing muitiple inclusion error
 *  it is fine to remove them if you want
 */

#include "tools.h"
#include "hashtable_mlist.h"

/*
 *   I lied, there's only In, no out functions.
 */

// RECORD ALL THE dictionary FROM FILE INTO THE HASHTABLE
extern void recordWord(char *filename, HASHTABLE_MLIST *hashtable);

#endif