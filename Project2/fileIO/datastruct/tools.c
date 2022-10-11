//  CITS2002 Project 2 2022
//  Student:   23006364   HU   ZHUO   100

#include "tools.h"

int ARG_MAX = 2097152;
int wordlen = 4;

// DJBHASH FUNCTION FOR HASHING STRING
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

// CHECK IF THE CHAR CAN BUILDING A WORD
bool isWord(char c)
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

// CHANGE THE WORDLEN
void change_wordlen(int len)
{
    wordlen = len;
}

// CHECK IF THE WORD LEN IS GREATER THAN KEYLEN
bool wordlen_check(char *word)
{
    char *tmp = word;
    int len = strlen(tmp);
    if (len >= wordlen)
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
        perror("fopen");
        exit(EXIT_FAILURE);
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

// GET ONE LINE FROM THE FILE
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

// A FUNCTION CHANGE THE GIVEN INT TO STRING
char *itoa(int num)
{
    char *str = (char *)malloc(20);
    sprintf(str, "%d", num);
    return str;
}

// CHECK IF THE GIVEN STRING IS A INTERGER
bool isInt(char *str)
{
    if (strcmp(itoa(atoi(str)), str) == 0)
    {
        return true;
    }
    return false;
}

// CHECK IF THE GIVEN NAME IS A FILE
bool isFile(char *name)
{
    struct stat statbuf;
    if (stat(name, &statbuf) != 0)
    {
        return false;
    }
    return S_ISREG(statbuf.st_mode);
}

// CHECK IF THE GIVEN NAME IS DIRECTORY
bool isDirectory(char *name)
{
    struct stat statbuf;
    if (stat(name, &statbuf) != 0)
    {
        return false;
    }
    return S_ISDIR(statbuf.st_mode);
}