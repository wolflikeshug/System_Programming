#define _POSIX_C_SOURCE 200809L

#include "tools.h"

// DJBHASH FUNCTION FOR HASH STRING
uint64_t DJBHash(char *string)
{
    uint64_t hash = 5381;
    int c;

    while (c = *string++)
        hash = ((hash << 5) + hash) + c;

    return hash;
}

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
    if (c == '_')
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
    int len = strlen(word);
    if (len > keylen)
    {
        return true;
    }
    return false;
    
}

int main(void)
{
    keylen = 4;
    return 0;
}