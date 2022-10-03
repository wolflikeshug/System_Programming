#include "tools.h"

// GET THE FILE SIZE OF THE INDEX FILE
int file_getsize(FILE *file)
{
    int size;
    FILE *tmp = file;

    fseek(tmp, 0, SEEK_END);
    size = ftell(tmp);
    fseek(tmp, 0, SEEK_SET);
    return size;
}
