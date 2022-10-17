//  CITS2002 Project 2 2022
//  Student:   23006364   HU   ZHUO   100

#include "tools.h"

int  ARG_MAX = 2097152;
int  wordlen = 4;          // word limit cannot larger than 2^31-1

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
void change_wordlen(int len)
{
    wordlen = len;
}

// CHECK IF THE WORD LEN IS GREATER THAN KEYLEN
bool wordlen_check(char *word)
{
    char *tmp = word;
    unsigned long long len = strlen(tmp);
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

// GET ONE LINE FROM THE FILE
char *getLine(FILE *file)
{
    char *line = (char *)malloc(1);
    char c;
    unsigned long long i = 0;
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

// CALCULATE MD5 HASH OF THE GIVEN FILE
char *md5sum(char *filename)
{
    char *md5 = (char *)malloc(33);
    char *cmd = strdup("md5sum '");
    cmd = realloc(cmd, strlen(cmd) + strlen(filename) + 2);
    strcat(cmd, filename);
    strcat(cmd, "'");
    FILE *terminal = popen(cmd, "r");
    md5 = getLine(terminal);
    md5[32] = '\0';
    pclose(terminal);
    return md5;
}

// CHECK IF THE STORED MD5 HASH IS THE SAME AS THE MD5 HASH OF THE FILE
bool md5check(char *md5, char *filename)
{
    char *md5new = md5sum(filename);
    if (strcmp(md5, md5new) == 0)
    {
        free(md5new);
        return true;
    }
    free(md5new);
    return false;
}