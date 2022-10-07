#define _POSIX_C_SOURCE 20089L
#define _GNU_SOURCE

#include "wordFileIO.h"

// RECORD ALL THE WORDS FROM FILE INTO THE HASHTABLE
void recordWord(char *filename, HASHTABLE_MLIST *hashtable)
{
    filename = getRealPath(filename);
    printf("Recording File: \"%s\"\n", filename);
    FILE *fp = openfile(filename);
    char *word = (char *)malloc(sizeof(char) * 1);
    memset(word, '\0', 1);
    int len = 0;     // length of the word
    char tmp[20000]; // store the word temporarily
    tmp[0] = '\0';
    char c = fgetc(fp);
    while (!feof(fp))
    {
        if (stillWord(c))
        {
            tmp[len] = c;
            len++;
        }
        else
        {
            tmp[len] = '\0';
            word = strdup(tmp);
            len = 0;
            tmp[len] = '\0';
            if (wordlen_check(word))
            {
                hashtable_mlist_add(hashtable, filename, word);
            }
        }
        c = fgetc(fp);
    }

    fclose(fp);
    free(word);
}