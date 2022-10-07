#define _POSIX_C_SOURCE 20089L
#define _GNU_SOURCE

#include "tools.h"

int ARG_MAX = 2097152;
int keylen = 4;

// DJBHASH FUNCTION FOR HASH STRING
uint64_t DJBHash(char *string)
{
    uint64_t hash = 5381;
    char c = *string;

    while (c != '\0')
    {
        hash = hash * 33 + c;
        c = *++string;
    }
    return hash;
}

// GET THE FILE SIZE OF THE TROVE FILE
int file_getsize(FILE *file)
{
    int size;
    FILE *tmp = file;

    fseek(tmp, 0, SEEK_END);
    size = ftell(tmp);
    fseek(tmp, 0, SEEK_SET);
    return size;
}

// CHECK IF THE CHAR CAN KEEP BUILDING THE KEY
bool stillWord(char c)
{
    // ONLY TAKE 'A-Z', 'a-z', '0-9'
    if (c >= 'a' && c <= 'z')
    {
        return true;
    }
    if (c >= 'A' && c <= 'Z')
    {
        return true;
    }
    if (c >= '0' && c <= '9')
    {
        return true;
    }
    return false;
}

// CHANGE THE KEYLEN
void change_keylen(int len)
{
    keylen = len;
}

// CHECK IF THE WORD LEN IS GREATER THAN KEYLEN
bool wordlen_check(char *word)
{
    char *tmp = word;
    int len = strlen(tmp);
    if (len >= keylen)
    {
        return true;
    }
    return false;
}

// IF THE FILE IS NOT EXIST POP UP ERROR MESSAGE
// IF THE FILE IS EXIST RETURN THE FILE POINTER
FILE *openfile(char *filename)
{
    FILE *file = fopen(filename, "r+");
    if (file == NULL)
    {
        printf("File %s does not exist\n", filename);
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    return file;
}

// CHECK IF THE FILE IS EXIST, IF EXIST DO NOTHING IF NOT EXIT POP ERROR MESSAGE
bool file_exist(char *filename)
{
    FILE *file = fopen(filename, "r+");
    if (file == NULL)
    {
        return false;
    }
    fclose(file);
    return true;
}

// GET THE REAL PATH OF THE FILE
char *getRealPath(char *filename)
{
    char *fileRealPath = (char *)malloc(PATH_MAX);
    realpath(filename, fileRealPath);
    return fileRealPath;
}

// GET ONE LINE FROM THE FILE DINAMICALLY
char *getLine(FILE *file)
{
    char *line = (char *)malloc(1);
    char c;
    int i = 0;
    while (!feof(file))
    {
        c = fgetc(file);
        if (c != '\n')
        {
            line[i] = c;
            i++;
            line = (char *)realloc(line, i + 1);
        }
        else
        {
            line[i] = '\0';
            break;
        }
    }
    return line;
}

