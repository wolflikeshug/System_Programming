#define _POSIX_C_SOURCE 200809L

#include "wordFileIO.h"

// PUT THE WORD INTO HASHTABLE_LIST
void store_word(HASHTABLE_LIST *hashtable, char *word)
{
    hashtable_list_add(hashtable, word);
}

// RECORD ALL THE WORDS FROM FILE INTO THE HASHTABLE
void recordWord(FILE *fp, char *filename, HASHTABLE_MLIST *hashtable)
{

    char *word = (char *)malloc(sizeof(char) * 1);
    memset(word, '\0', 1);
    int len = 0; // length of the word
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
                store_word(hashtable_mlist_filename_list(hashtable, filename), word);
            }
        }
        c = fgetc(fp);
    }
    free(word);
}

