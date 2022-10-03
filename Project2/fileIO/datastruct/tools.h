#ifndef _TOOLS_H
#define _TOOLS_H

#include <stdlib.h>

// CHECK IF THE MEMORY ALLOCATION WAS SUCCESSFUL 
#define CHECK_MEM(p) if(p == NULL) { perror(__func__); exit(EXIT_FAILURE); }

// GET THE FILE SIZE OF THE INDEX FILE
extern int file_getsize(FILE * file);

// FIND OUT THE NUM OF CORES IN THE SYSTEM
extern int GET_NUM_CORES(void);

#endif