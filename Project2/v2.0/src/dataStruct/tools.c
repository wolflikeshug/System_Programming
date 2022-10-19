/*
 *   CITS2002  Project 2  2022-sem2
 *   Student:  23006364   HU ZHUO   100
 */

#include "tools.h"

uint32_t ARG_MAX = 2097152;
uint32_t wordlen = 4;

// DJBHASH FUNCTION FOR HASHING STRING
uint16_t DJBHash(char *string)
{
    uint16_t hash = 5381;
    char c = *string;

    while (c != '\0')
    {
        hash = hash * 33 + c;
        c = *++string;
    }
    return hash;
}

// CHECK IF THE STRING IS A WORD
bool isString(char *string)
{
    char c = *string;
    while (c != '\0')
    {
        if (!isalnum(c))
        {
            return false;
        }
        c = *++string;
    }
    return true;
}

// CHANGE THE WORDLEN
void change_wordlen(uint32_t len)
{
    wordlen = len;
}

// CHECK IF THE WORD LEN IS GREATER THAN KEYLEN
bool wordlen_check(char *word)
{
    char *tmp = word;
    uint32_t len = strlen(tmp);
    if (len >= wordlen)
    {
        return true;
    }
    return false;
}

// IF THE FILE IS EXIST RETURN THE FILE POINTER OTHERWISE POP UP ERROR MESSAGE
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

// GET THE REAL PATH OF THE FILE
char *getRealPath(char *filename)
{
    char *fileRealPath = (char *)calloc(PATH_MAX, sizeof(char));
    CHECK_MEM(fileRealPath);

    realpath(filename, fileRealPath);
    return fileRealPath;
}

// GET ONE LINE FROM THE FILE
char *getLine(FILE *file)
{
    char *line = (char *)calloc(1000, sizeof(char));
    CHECK_MEM(line);

    char c = fgetc(file);
    uint64_t len = 0;

    while (!feof(file))
    {
        if (c != '\n')
        {
            line[len] = c;
            len++;
            if (len > 1000)
            {
                line = (char *)realloc(line, sizeof(char) * (len + 2));
            }
        }
        else
        {
            line[len] = '\0';
            break;
        }
        c = fgetc(file);
    }
    return line;
}

// A FUNCTION CHANGE THE GIVEN INT TO STRING
char *itoa(uint16_t num)
{
    char *str = (char *)calloc(20, sizeof(char));
    CHECK_MEM(str);

    sprintf(str, "%d", num);
    return str;
}

// CHECK IF THE GIVEN STRING IS A INTERGER
bool isInt(char *str)
{
    if (!strcmp(itoa(atoi(str)), str))
    {
        return true;
    }
    return false;
}

// CHECK IF THE GIVEN NAME IS A FILE
bool isFile(char *name)
{
    struct stat statbuf;
    if (stat(name, &statbuf))
    {
        return false;
    }
    return S_ISREG(statbuf.st_mode);
}

// CHECK IF THE GIVEN NAME IS DIRECTORY
bool isDirectory(char *name)
{
    struct stat statbuf;
    if (stat(name, &statbuf))
    {
        return false;
    }
    return S_ISDIR(statbuf.st_mode);
}

// CALCULATE MD5 HASH OF THE GIVEN FILE
char *md5sum(char *filename)
{
    char *md5 = (char *)calloc(33, sizeof(char));
    CHECK_MEM(md5);
    char *cmd = strdup("md5sum '");

    cmd = (char *)realloc(cmd, sizeof(char) * (strlen(cmd) + strlen(filename) + 2));
    strcat(cmd, filename);
    strcat(cmd, "'");

    FILE *terminal = popen(cmd, "r");

    fgets(md5, sizeof(char) * 33, terminal);
    md5[32] = '\0';

    pclose(terminal);
    free(cmd);

    return md5;
}

// CHECK IF THE STORED MD5 HASH IS THE SAME AS THE MD5 HASH OF THE FILE
bool md5check(char *md5, char *filename)
{
    char *md5new = md5sum(filename);
    if (!strcmp(md5, md5new))
    {
        free(md5new);
        return true;
    }
    free(md5new);
    return false;
}